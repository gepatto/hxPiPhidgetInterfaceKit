#ifndef STATIC_LINK
#define IMPLEMENT_API
#endif

#if defined(HX_WINDOWS) || defined(HX_MACOS) || defined(HX_LINUX)
#define NEKO_COMPATIBLE
#endif

#include <hx/CFFI.h>
#include <string.h>
#include "hxPiPhidgetInterfaceKit.h"

using namespace hxpiphidgetinterfacekit;

/**
*
*/
static void hxpiphidgetinterfacekit_initialize()
{
	initialize();	
}
DEFINE_PRIM (hxpiphidgetinterfacekit_initialize, 0);

/**
*
*/
static void hxpiphidgetinterfacekit_shutdown()
{
  shutdown();
}
DEFINE_PRIM(hxpiphidgetinterfacekit_shutdown, 0);

/**
*
*/
static void hxpiphidgetinterfacekit_setSensorsChangeTrigger(value sensorThreshold)
{
  setSensorsChangeTrigger(val_int(sensorThreshold));
}
DEFINE_PRIM(hxpiphidgetinterfacekit_setSensorsChangeTrigger, 1);

/**
*
*/
static void hxpiphidgetinterfacekit_setSensorChangeTrigger(value channel , value sensorThreshold)
{
  setSensorChangeTrigger(val_int(channel), val_int(sensorThreshold));
}
DEFINE_PRIM(hxpiphidgetinterfacekit_setSensorChangeTrigger, 2);

/**
*
*/
static void hxpiphidgetinterfacekit_set_haxe_callback_for_dispatching_events(value haxeCallback)
{
   AutoGCRoot* callback = new AutoGCRoot(haxeCallback);
   hxpiphidgetinterfacekit::SetHaxeCallbackForDispatchingEvents(callback);
}
DEFINE_PRIM(hxpiphidgetinterfacekit_set_haxe_callback_for_dispatching_events, 1);

/**
*
*/
extern "C" void hxpiphidgetinterfacekit_main () {
	
	val_int(0); // Fix Neko init
	
}
DEFINE_ENTRY_POINT (hxpiphidgetinterfacekit_main);

extern "C" int hxpiphidgetinterfacekit_register_prims () { return 0; }