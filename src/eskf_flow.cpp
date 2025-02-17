//
// Created by meng on 2021/2/24.
//
#include "config_parameters.h"
#include "eskf_flow.h"
#include "common_tool.h"

#include <iomanip>
#include <fstream>
#include <utility>
#include <yaml-cpp/yaml.h>

ESKFFlow::ESKFFlow(const std::string &config_file_path, std::string data_file_path)
        : config_file_path_(config_file_path), data_file_path_(std::move(data_file_path)) {
    config_parameters_.LoadParameters(config_file_path);

    gps_flow_ptr_ = std::make_shared<GPSTool>(config_parameters_.ref_longitude_, config_parameters_.ref_latitude_);
    eskf_ptr_ = std::make_shared<ErrorStateKalmanFilter>(config_parameters_);
}

void ESKFFlow::ReadData() {
    imu_flow_ptr_->ReadIMUData(data_file_path_ + "/raw_data", imu_data_buff_);
    gps_flow_ptr_->ReadGPSData(data_file_path_ + "/raw_data", gps_data_buff_);
}

bool ESKFFlow::ValidGPSAndIMUData() {
    curr_imu_data_ = imu_data_buff_.front();
    curr_gps_data_ = gps_data_buff_.front();

    double delta_time = curr_imu_data_.time - curr_gps_data_.time;
    if (delta_time > 0.01) {
        gps_data_buff_.pop_front();
        return false;
    }

    if (delta_time < -0.01) {
        imu_data_buff_.pop_front();
        return false;
    }

    imu_data_buff_.pop_front();
    gps_data_buff_.pop_front();

    return true;
}

bool ESKFFlow::Run() {
    ReadData();

    while (!imu_data_buff_.empty() && !gps_data_buff_.empty()) {
        if (!ValidGPSAndIMUData()) {
            continue;
        } else {
            eskf_ptr_->Init(curr_gps_data_, curr_imu_data_);
            break;
        }
    }
    std::ofstream fused_file(data_file_path_ + "/fused.txt", std::ios::trunc);
    std::ofstream measured_file(data_file_path_ + "/gps_measurement.txt", std::ios::trunc);

    LOG(INFO) << "Start fuse IMU and GPS ...";
    while (!imu_data_buff_.empty() && !gps_data_buff_.empty()) {
        curr_imu_data_ = imu_data_buff_.front();
        curr_gps_data_ = gps_data_buff_.front();
        if (curr_imu_data_.time < curr_gps_data_.time) {
            eskf_ptr_->Predict(curr_imu_data_);
            imu_data_buff_.pop_front();
        } else {
            eskf_ptr_->Predict(curr_imu_data_);
            imu_data_buff_.pop_front();


            if (!config_parameters_.only_prediction_){
                eskf_ptr_->Correct(curr_gps_data_);
            }

            SaveTUMPose(fused_file, Eigen::Quaterniond(eskf_ptr_->GetPose().topLeftCorner<3, 3>()),
                        eskf_ptr_->GetPose().topRightCorner<3, 1>(), curr_imu_data_.time);

            SaveTUMPose(measured_file, Eigen::Quaterniond::Identity(),
                        curr_gps_data_.local_position_ned, curr_gps_data_.time);

            gps_data_buff_.pop_front();
        }

        if (use_observability_analysis_) {
            Eigen::Matrix<double, 15, 15> F;
            Eigen::Matrix<double, 3, 15> G;
            Eigen::Matrix<double, 3, 1> Y;
            eskf_ptr_->GetFGY(F, G, Y);
            observability_analysis.SaveFG(F, G, Y, curr_gps_data_.time);
        }
    }

    if (use_observability_analysis_) {
        observability_analysis.ComputeSOM();
        observability_analysis.ComputeObservability();
    }

    LOG(INFO) << "End fuse IMU and GPS";
    LOG(INFO) << "fused data in: " << data_file_path_ + "/fused.txt";
    LOG(INFO) << "GPS data in: " << data_file_path_ + "/gps_measurement.txt";

    return true;
}

bool ESKFFlow::Run_onlyIMUpred() {
    ReadData();

    while (!imu_data_buff_.empty() && !gps_data_buff_.empty()) {
        if (!ValidGPSAndIMUData()) {
            continue;
        } else {
            eskf_ptr_->Init(curr_gps_data_, curr_imu_data_);
            break;
        }
    }
    LOG(INFO) << "Start IMU solve ...";
    std::ofstream imu_file(data_file_path_ + "/imu.txt", std::ios::trunc);

    while (!imu_data_buff_.empty() && !gps_data_buff_.empty()) {
        curr_imu_data_ = imu_data_buff_.front();
        curr_gps_data_ = gps_data_buff_.front();
        eskf_ptr_->Predict(curr_imu_data_);
        imu_data_buff_.pop_front();
        SaveTUMPose(imu_file, Eigen::Quaterniond(eskf_ptr_->GetPose().topLeftCorner<3, 3>()),
                        eskf_ptr_->GetPose().topRightCorner<3, 1>(), curr_imu_data_.time);
    }
    LOG(INFO) << "End IMU solve";
    LOG(INFO) << "imu data in: " << data_file_path_ + "/imu.txt";
    return true;
}

void ESKFFlow::SavePose(std::ofstream &ofs, const Eigen::Matrix4d &pose) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            ofs << pose(i, j);

            if (i == 2 && j == 3) {
                ofs << std::endl;
            } else {
                ofs << " ";
            }
        }
    }
}

void ESKFFlow::SaveTUMPose(std::ofstream &ofs, const Eigen::Quaterniond &q,
                           const Eigen::Vector3d &t, double timestamp) {
    ofs << std::fixed << std::setprecision(10) << timestamp << " " << t.x() << " " << t.y() << " " << t.z() << " "
        << q.x() << " " << q.y() << " " << q.z() << " " << q.w() << std::endl;
}
