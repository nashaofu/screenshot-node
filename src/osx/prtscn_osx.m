#include <ApplicationServices/ApplicationServices.h>
#include <CoreGraphics/CoreGraphics.h>
#include <CoreServices/CoreServices.h>
#include <ImageIO/ImageIO.h>
#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>
#include "prtscn_osx.h"

// CGImageRef转换为NSData
NSData * CGimageRefToNSData(CGImageRef imageRef)
{
	CFMutableDataRef dataRef = CFDataCreateMutable(NULL, 0);
	CGImageDestinationRef destinationRef = CGImageDestinationCreateWithData(dataRef, kUTTypePNG, 1, NULL);
	CGImageDestinationAddImage(destinationRef, imageRef, nil);
	CGImageDestinationFinalize(destinationRef);
	NSData *data = [NSData dataWithData:(NSData *)dataRef];
	CFRelease(destinationRef);
	CFRelease(dataRef);
	return data;
}

IData getScreen(const int x, const int y, const int width, const int height)
{	
	CGRect rect = CGRectMake(x, y, width, height);
	CGImageRef imageRef = CGDisplayCreateImageForRect(CGMainDisplayID(), rect);
	
	NSData * data = CGimageRefToNSData(imageRef);
	unsigned int length = [data length];

	UInt8 *byteData = (UInt8 *)[data bytes];
	CGImageRelease(imageRef);

	IData idd = {
		length,
		byteData
	};
	return idd;
}
