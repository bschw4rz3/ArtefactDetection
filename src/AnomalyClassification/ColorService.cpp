#include "ColorService.h"

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