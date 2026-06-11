#include "ColorService.h"

ColorRGB ColorService::byte2rgb(const unsigned char* ptr, int imageWidth, int imageHeight)
{
	unsigned char r = ptr[0];
	unsigned char g = ptr[0 + imageWidth * imageHeight];
	unsigned char b = ptr[0 + 2 * imageWidth * imageHeight];

	return ColorRGB(r, g, b);
}

const unsigned char* ColorService::rgb2byte(ColorRGB colorRgb)
{
	const unsigned char(&color)[3] = { (unsigned char) colorRgb.r, (unsigned char) colorRgb.g, (unsigned char) colorRgb.b };
	return color;
}

ColorLib ColorService::rgb2lab(ColorRGB color) {
	double r = this->rgb2lab_normalizeRgbChannel(color.r);
	double g = this->rgb2lab_normalizeRgbChannel(color.g);
	double b = this->rgb2lab_normalizeRgbChannel(color.b);

	double X = r * 0.4124 + g * 0.3576 + b * 0.1805;
	double Y = r * 0.2126 + g * 0.7152 + b * 0.0722;
	double Z = r * 0.0193 + g * 0.1192 + b * 0.9505;

	// Observer= 2°, Illuminant= D65
	X = this->rgb2lab_normalizeXyzChannel(X / 95.0470);
	Y = this->rgb2lab_normalizeXyzChannel(Y / 100.0);
	Z = this->rgb2lab_normalizeXyzChannel(Z / 108.883);

	return ColorLib(
		(116 * Y) - 16, // L
			500 * (X - Y),  // a
			200 * (Y - Z)  // b
	);
}

double ColorService::rgb2lab_normalizeRgbChannel(double channel) {
	channel /= 255;

	return 100.0 * (channel > 0.04045
		? pow((channel + 0.055) / 1.055, 2.4)
		: channel / 12.92
		);
}

double ColorService::rgb2lab_normalizeXyzChannel(double channel) {
	return (channel > 0.008856)
		? pow(channel, 1.0 / 3.0)
		: (7.787 * channel) + (16.0 / 116.0);
}