Device configuration for the Samsung Galaxy Note Pro 12.2

Copyright (C) 2017 The LineageOS Project
Copyright (C) 2017 Valera Chigir <valera1978@tut.by>

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

------------------------------------------------------------------

* Description

  This repository is for LineageOS on Samsung Galaxy Note Pro 12.2 (viennalte)

* How To Build LineageOS for Samsung Galaxy Note Pro 12.2

  - Make a workspace

mkdir cm14
cd cm14

  - Do repo init & sync

repo init -u git://github.com/LineageOS/android.git -b cm-14.1

  - Create .repo/local_manifests/roomservice.xml with the following content:

<?xml version="1.0" encoding="UTF-8"?>
<manifest>
  <project name="Valera1978/android_device_samsung_viennalte" path="device/samsung/viennalte" remote="github" revision="cm14.0" />
  <project name="Valera1978/android_kernel_samsung_viennalte" path="kernel/samsung/viennalte" remote="github" revision="cm14.0" />
  <project name="Valera1978/android_vendor_samsung_viennalte" path="vendor/samsung/viennalte" remote="github" revision="cm14.0" />
  <project name="LineageOS/android_external_sony_boringssl-compat" path="external/sony/boringssl-compat" remote="github" />
  <project name="LineageOS/android_device_samsung_msm8974-common" path="device/samsung/msm8974-common" remote="github" />
  <project name="LineageOS/android_device_qcom_common" path="device/qcom/common" remote="github" />
  <project name="LineageOS/android_device_samsung_qcom-common" path="device/samsung/qcom-common" remote="github" />
  <project name="LineageOS/android_hardware_samsung" path="hardware/samsung" remote="github" />
  <project name="LineageOS/android_external_stlport" path="external/stlport" remote="github" />
</manifest>

repo sync

  - Copy proprietary vendor files

  There are two options to to that. Connect your device with adb enabled and run:

./extract-files.sh

  Or if you have the system image unpacked on your disk, then simply run:

    STOCK_ROM_DIR=/path/to/system ./extract-files.sh

  - Setup environment

. build/envsetup.sh

  - Build cm14

brunch viennalte

or another way:

lunch lineage_viennalte-userdebug
export USE_CCACHE=1
make -j10 bacon
