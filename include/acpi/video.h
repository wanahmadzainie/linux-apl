#ifndef __ACPI_VIDEO_H
#define __ACPI_VIDEO_H

#include <linux/errno.h> /* for ENODEV */

struct acpi_device;

#define ACPI_VIDEO_CLASS	"video"

#define ACPI_VIDEO_DISPLAY_CRT  1
#define ACPI_VIDEO_DISPLAY_TV   2
#define ACPI_VIDEO_DISPLAY_DVI  3
#define ACPI_VIDEO_DISPLAY_LCD  4

#define ACPI_VIDEO_DISPLAY_LEGACY_MONITOR 0x0100
#define ACPI_VIDEO_DISPLAY_LEGACY_PANEL   0x0110
#define ACPI_VIDEO_DISPLAY_LEGACY_TV      0x0200

enum acpi_backlight_type {
	acpi_backlight_undef = -1,
	acpi_backlight_none = 0,
	acpi_backlight_video,
	acpi_backlight_vendor,
	acpi_backlight_native,
};

#if (defined CONFIG_ACPI_VIDEO || defined CONFIG_ACPI_VIDEO_MODULE)
extern int acpi_video_register(void);
extern void acpi_video_unregister(void);
extern void acpi_video_unregister_backlight(void);
extern int acpi_video_get_edid(struct acpi_device *device, int type,
			       int device_id, void **edid);
extern bool acpi_video_verify_backlight_support(void);
extern enum acpi_backlight_type acpi_video_get_backlight_type(void);
extern void acpi_video_set_dmi_backlight_type(enum acpi_backlight_type type);
#else
static inline int acpi_video_register(void) { return 0; }
static inline void acpi_video_unregister(void) { return; }
static inline void acpi_video_unregister_backlight(void) { return; }
static inline int acpi_video_get_edid(struct acpi_device *device, int type,
				      int device_id, void **edid)
{
	return -ENODEV;
}
static inline bool acpi_video_verify_backlight_support(void) { return false; }
static inline enum acpi_backlight_type acpi_video_get_backlight_type(void)
{
	return acpi_backlight_vendor;
}
static void acpi_video_set_dmi_backlight_type(enum acpi_backlight_type type)
{
}
#endif

#endif
