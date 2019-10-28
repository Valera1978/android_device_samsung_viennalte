/*
 * Copyright (c) 2014 The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>

#define LOG_TAG "PowerHAL_K_Ext"
#include <utils/Log.h>

#define MAX_INPUTS 20
#define INPUT_PREFIX "/sys/class/input/input"
#define MAX_PATH_SIZE 256

static const char *names[] = {
    "sec_touchscreen", // 3
    "sec_e-pen" // 4
    "accelerometer_sensor" // 6
    "gyro_sensor" // 7
    "magnetic_sensor" // 8
    "light_sensor" // 9
    "grip_sensor" // 10
    "gpio-keys" // 11
};
#define N_NAMES (sizeof(names) / sizeof(names[0]))
static char paths[N_NAMES][MAX_PATH_SIZE];
static int have_found_paths;

static size_t sysfs_read(char *path, char *buffer, size_t n)
{
    char buf[MAX_PATH_SIZE];
    int fd;
    size_t len;

    if ((fd = open(path, O_RDONLY)) < 0)
    {
        if (errno != ENOENT)
        {
            strerror_r(errno, buf, sizeof(buf));
            ALOGE("Error opening %s: %s\n", path, buf);
        }
        return 0;
    }

    len = read(fd, buffer, n);
    if (len < 0)
    {
        strerror_r(errno, buf, sizeof(buf));
        ALOGE("Error reading from %s: %s\n", path, buf);
        return 0;
    }

    while (len > 0 && isspace(buffer[len-1]))
        len--;
    if (len < n)
        buffer[len] = '\0';

    close(fd);

    return len;
}

static void sysfs_write(char *path, char *s)
{
    char buf[MAX_PATH_SIZE];

    int fd = open(path, O_WRONLY);
    if (fd < 0)
    {
        strerror_r(errno, buf, sizeof(buf));
        ALOGE("Error opening %s: %s\n", path, buf);
        return;
    }

    size_t len = write(fd, s, strlen(s));
    if (len < 0)
    {
        strerror_r(errno, buf, sizeof(buf));
        ALOGE("Error writing to %s: %s\n", path, buf);
    }

    close(fd);
}

static void find_paths(void)
{
    size_t i, j;
    char path[MAX_PATH_SIZE];
    char name[MAX_PATH_SIZE];

    for (i = 0; i < N_NAMES; i++)
        paths[i][0] = 0;

    for (i = 0; i < MAX_INPUTS; i++)
    {
        sprintf(path, "%s%d/name", INPUT_PREFIX, i);
        if (sysfs_read(path, name, sizeof(name)) > 0)
        {
            for (j = 0; j < N_NAMES; j++)
            {
                if (strcmp(name, names[j]) == 0)
                {
                    sprintf(paths[j], "%s%d/enabled", INPUT_PREFIX, i);
                    ALOGD("%s => %s\n", names[j], paths[j]);
                }
            }
        }
    }
}

void power_set_interactive_ext(int on)
{
    ALOGD("%s: %s input devices", __func__, on ? "enabling" : "disabling");

    if (!have_found_paths)
    {
        find_paths();
        have_found_paths = 1;
    }

    for (size_t i = 0; i < N_NAMES; i++)
        sysfs_write(paths[i], on ? "1" : "0");
}

void cm_power_set_interactive_ext(int on)
{
    power_set_interactive_ext(on);
}
