import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d


def load_txt_data(data_path):
    try:
        return np.loadtxt(data_path)
    except FileNotFoundError as err:
        print('this is a OSError: ' + str(err))


if __name__ == "__main__":
    imu_data_path = './imu.txt'
    gps_data_path = './gps_measurement.txt'
    fused_data_path = './fused.txt'

    imu_data = load_txt_data(imu_data_path)
    gps_data = load_txt_data(gps_data_path)
    fused_data = load_txt_data(fused_data_path)

    fig = plt.figure()
    ax = plt.axes(projection='3d')
    ax.set_title('compare path')
    ax.plot3D(imu_data[:, 1], imu_data[:, 2], imu_data[:, 3], color='r', label='imu')
    ax.plot3D(gps_data[:, 1], gps_data[:, 2], gps_data[:, 3], color='g', alpha=0.5, label='gps')
    ax.plot3D(fused_data[:, 1], fused_data[:, 2], fused_data[:, 3], color='b', alpha=0.5, label='fused')
    plt.legend(loc='best')
    plt.show()
