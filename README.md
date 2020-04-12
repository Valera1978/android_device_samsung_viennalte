## TWRP device tree for Samsung Galaxy Note Pro 12.2 SM-P905
## viennalte

https://github.com/minimal-manifest-twrp/platform_manifest_twrp_omni/tree/twrp-9.0

Add to `.repo/local_manifests/viennalte.xml`:

```xml
<?xml version="1.0" encoding="UTF-8"?>
<manifest>
  <project name="valera1978/android_device_samsung_viennalte" path="device/samsung/viennalte" remote="github" revision="twrp" />
</manifest>
```

Then run `repo sync` to check it out.

To build:

```sh
export ALLOW_MISSING_DEPENDENCIES=true; . build/envsetup.sh; lunch omni_viennalte-eng; mka recoveryimage
```
or
```sh
export ALLOW_MISSING_DEPENDENCIES=true
. build/envsetup.sh
lunch omni_viennalte-eng
mka recoveryimage
```
