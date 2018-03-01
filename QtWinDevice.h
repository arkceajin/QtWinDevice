#ifndef QTWINDEVICE_H
#define QTWINDEVICE_H

#ifdef __WIN32
#include <QDir>
#include <windows.h>

/**
 * @brief Get the information of accessible drives in Win32 via Qt
 * @author jiu
 */
namespace QtWinDevice {
    /**
     * @brief The DeviceType enum
     */
    enum DeviceType{
        Unknown = DRIVE_UNKNOWN,
        NoRootDir = DRIVE_NO_ROOT_DIR,
        Removable = DRIVE_REMOVABLE,
        Fixed = DRIVE_FIXED,
        Remote = DRIVE_REMOTE,
        CDROM = DRIVE_CDROM,
        RAMDisk = DRIVE_RAMDISK
    };

    /**
     * @brief getRWDevices
     * @param type
     * @return devices
     */
    QFileInfoList getRWDevices(DeviceType type){
        QFileInfoList devices;
        foreach(QFileInfo f, QDir::drives()){
            QString path = f.absolutePath().replace("/", "\\");
            if(type == GetDriveType((LPCWSTR)(path.utf16())) && f.isReadable() && f.isWritable()){
                devices << f;
            }
        }
        return devices;
    }

    /**
     * @brief getUsbStorages
     * @return Removable devices
     */
    QFileInfoList getUsbStorages() {
        return getRWDevices(Removable);
    }
}
#endif

#endif // QTWINDEVICE_H
