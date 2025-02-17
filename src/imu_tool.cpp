//
// Created by meng on 2021/2/19.
//
#include "common_tool.h"
#include "imu_tool.h"

#include <glog/logging.h>

#include <fstream>
#include <iostream>

void IMUTool::ReadIMUData(const std::string &path, std::vector<IMUData> &imu_data_buff, const int skip_rows) {
    LOG(INFO) << "Read IMU data ...";
    std::string accel_file_path = path + "/accel-0.csv";
    std::string gyro_file_path = path + "/gyro-0.csv";
    std::string time_file_path = path + "/time.csv";

    std::ifstream accel_file(accel_file_path);
    std::ifstream gyro_file(gyro_file_path);
    std::ifstream time_file(time_file_path);

    if (!accel_file.is_open() || !gyro_file.is_open() || !time_file.is_open()) {
        LOG(FATAL) << "Failure to open IMU file";
    }

    IMUData imu_data;
    imu_data_buff.clear();

    std::string accel_line;
    std::string gyro_line;
    std::string time_line;
    std::string temp;

    for (int i = 0; i < skip_rows; ++i) {
        std::getline(accel_file, temp);
        std::getline(gyro_file, temp);
        std::getline(time_file, temp);
    }

    while (std::getline(accel_file, accel_line) &&
           std::getline(gyro_file, gyro_line) &&
           std::getline(time_file, time_line)
           ) {
        imu_data.time = std::stod(time_line)*1e-4;

        std::stringstream ss;
        ss << accel_line;

        std::getline(ss, temp, ',');
        imu_data.linear_accel.y() = std::stod(temp);//!!!导航坐标系enu-ned
        std::getline(ss, temp, ',');
        imu_data.linear_accel.x() = std::stod(temp);
        std::getline(ss, temp, ',');
        imu_data.linear_accel.z() = std::stod(temp)*(-1);


        ss.clear();
        ss << gyro_line;
        std::getline(ss, temp, ',');
        imu_data.angle_velocity.y() = std::stod(temp) ;
        std::getline(ss, temp, ',');
        imu_data.angle_velocity.x() = std::stod(temp) ;
        std::getline(ss, temp, ',');
        imu_data.angle_velocity.z() = std::stod(temp) * (-1);


        imu_data_buff.emplace_back(imu_data);
    }

    LOG(INFO) << "Read IMU data successfully";
}

void IMUTool::ReadIMUData(const std::string &path, std::deque<IMUData> &imu_data_buff, const int skip_rows) {
    LOG(INFO) << "Read IMU data ...";
    std::string accel_file_path = path + "/accel-0.csv";
    std::string gyro_file_path = path + "/gyro-0.csv";
    std::string time_file_path = path + "/time.csv";

    std::ifstream accel_file(accel_file_path);
    std::ifstream gyro_file(gyro_file_path);
    std::ifstream time_file(time_file_path);

    if (!accel_file.is_open() || !gyro_file.is_open() || !time_file.is_open()) {
        LOG(FATAL) << "Failure to open IMU file";
    }

    IMUData imu_data;
    imu_data_buff.clear();

    std::string accel_line;
    std::string gyro_line;
    std::string time_line;
    std::string temp;

    for (int i = 0; i < skip_rows; ++i) {
        std::getline(accel_file, temp);
        std::getline(gyro_file, temp);
        std::getline(time_file, temp);
    }

    while (std::getline(accel_file, accel_line) &&
           std::getline(gyro_file, gyro_line) &&
           std::getline(time_file, time_line)
           ) {
        imu_data.time = std::stod(time_line)*1e-4;

        std::stringstream ss;
        ss << accel_line;

        std::getline(ss, temp, ',');
        imu_data.linear_accel.y() = std::stod(temp);//!!!导航坐标系enu-ned
        std::getline(ss, temp, ',');
        imu_data.linear_accel.x() = std::stod(temp);
        std::getline(ss, temp, ',');
        imu_data.linear_accel.z() = std::stod(temp)*(-1);


        ss.clear();
        ss << gyro_line;
        std::getline(ss, temp, ',');
        imu_data.angle_velocity.y() = std::stod(temp) ;
        std::getline(ss, temp, ',');
        imu_data.angle_velocity.x() = std::stod(temp) ;
        std::getline(ss, temp, ',');
        imu_data.angle_velocity.z() = std::stod(temp) * (-1);


        imu_data_buff.emplace_back(imu_data);
    }

    LOG(INFO) << "Read IMU data successfully";
}
