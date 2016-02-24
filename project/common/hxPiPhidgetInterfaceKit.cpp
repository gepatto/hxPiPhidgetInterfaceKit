#include <hx/CFFI.h>
#include <stdio.h>
#include <stdarg.h>
#include <phidget21.h>
#include "hxPiPhidgetInterfaceKit.h"

static AutoGCRoot* g_haxeCallbackForDispatchingEvents = NULL;

struct AutoHaxe
{
	int base;
	const char *message;
	AutoHaxe(const char *inMessage)
	{  
		base = 0;
		message = inMessage;
		gc_set_top_of_stack(&base,true);
	}
	~AutoHaxe()
	{
		gc_set_top_of_stack(0,true);
	}
};

namespace hxpiphidgetinterfacekit {

	CPhidgetInterfaceKitHandle ifKit = 0;

	/**
	*
	*/
	AutoGCRoot* GetHaxeCallbackForDispatchingEvents()
    {
        return g_haxeCallbackForDispatchingEvents;
    }
    
	/**
	*
	*/
    void SetHaxeCallbackForDispatchingEvents(AutoGCRoot* haxeCallback)
    {
        if (g_haxeCallbackForDispatchingEvents)
        {
            delete g_haxeCallbackForDispatchingEvents;
        }

        g_haxeCallbackForDispatchingEvents = haxeCallback;
    }
    /**
	*
	*/
	void InvokeHaxeCallbackFunctionForDispatchingEvents(int eventDispatcherId, const char* eventClassSpec, va_list params)
	{
		bool foundAllArgs = false;
		value ar = alloc_array(0);

		while (!foundAllArgs)
		{
			int type = va_arg(params, int);
			switch (type)
			{
				case CEND:
					foundAllArgs = true;
					break;

				case CSTRING:
					val_array_push(ar, alloc_string(va_arg(params, char*)));
					break;

				case CINT:
					val_array_push(ar, alloc_int(va_arg(params, int)));
					break;

				case CDOUBLE:
					val_array_push(ar, alloc_float(va_arg(params, double)));
					break;

				default:
					printf("InvokeHaxeCallbackFunctionForDispatchingEvents() received invalid type %d, aborting.\n", type);
					return;
			}
		}

		AutoGCRoot* haxeCallback = GetHaxeCallbackForDispatchingEvents();
		if (haxeCallback != NULL)
		{
			val_call3( haxeCallback->get(), alloc_int(eventDispatcherId), alloc_string(eventClassSpec), ar);
		}
	}
	
	/**
	*
	*/
	void DispatchEventToHaxe(const char* eventClassSpec, ...)
	{
        va_list params;
        va_start(params, eventClassSpec);
		::AutoHaxe haxe("Invoke");
		InvokeHaxeCallbackFunctionForDispatchingEvents(0, eventClassSpec, params);
		
		va_end(params);
	}
	
	/**
	*
	*/
	void DispatchEventToHaxeInstance(int eventDispatcherId, const char* eventClassSpec, ...)
	{
        va_list params;
        va_start(params, eventClassSpec);
		
		InvokeHaxeCallbackFunctionForDispatchingEvents(eventDispatcherId, eventClassSpec, params);
		
		va_end(params);
	}
	
	/* ------------------------------------------------------------------------------
	|
	|  ------------------------------------------------------------------------------
	*/
	int CCONV AttachHandler(CPhidgetHandle IFK, void *userptr)
	{
		int serialNo;
		const char *name;

		CPhidget_getDeviceName(IFK, &name);
		CPhidget_getSerialNumber(IFK, &serialNo);

		setSensorsChangeTrigger(20);
		
		DispatchEventToHaxe("phidgets.event.IKEvent", 
			hxpiphidgetinterfacekit::CSTRING, "ik_event_device_attach",
			hxpiphidgetinterfacekit::CSTRING, name,
			hxpiphidgetinterfacekit::CINT, serialNo,  
			hxpiphidgetinterfacekit::CEND); 
		
		printf("%s %10d attached!\n", name, serialNo);
		return 0;
	}

	/**
	*
	*/
	int CCONV DetachHandler(CPhidgetHandle IFK, void *userptr)
	{
		int serialNo;
		const char *name;

		CPhidget_getDeviceName (IFK, &name);
		CPhidget_getSerialNumber(IFK, &serialNo);

		
		DispatchEventToHaxe( "phidgets.event.IKEvent", 
			hxpiphidgetinterfacekit::CSTRING,  "ik_event_device_detach",
			hxpiphidgetinterfacekit::CSTRING, name,
			hxpiphidgetinterfacekit::CINT, serialNo,
		 	hxpiphidgetinterfacekit::CEND); 
		
		printf("%s %10d detached!\n", name, serialNo);

		return 0;
	}

	/**
	*
	*/
	int CCONV ErrorHandler(CPhidgetHandle IFK, void *userptr, int ErrorCode, const char *unknown)
	{
		printf("Error handled. %d - %s", ErrorCode, unknown);
		return 0;
	}

	/**
	* callback that will run if an input changes.
	* @param Index - Index of the input that generated the event, 
	* @param State - boolean (0 or 1) representing the input state (on or off)
	*/
	int CCONV InputChangeHandler(CPhidgetInterfaceKitHandle IFKH, void *usrptr, int Index, int State)
	{

		DispatchEventToHaxe( "phidgets.event.IKDataEvent", 
			hxpiphidgetinterfacekit::CSTRING,  "ik_data_event_input_change",	
			hxpiphidgetinterfacekit::CINT, Index,  
			hxpiphidgetinterfacekit::CINT, State,
			hxpiphidgetinterfacekit::CEND); 
		return 0;
	}

	/**
	* callback that will run if an output changes..
	* @param Index - Index of the output that generated the event
	* @param State - boolean (0 or 1) representing the output state (on or off)
	*/
	int CCONV OutputChangeHandler(CPhidgetInterfaceKitHandle IFKH, void *usrptr, int Index, int State)
	{
		

		DispatchEventToHaxe( "phidgets.event.IKDataEvent", 
			hxpiphidgetinterfacekit::CSTRING,  "ik_data_event_output_change",	
			hxpiphidgetinterfacekit::CINT, Index,  
			hxpiphidgetinterfacekit::CINT, State,
			hxpiphidgetinterfacekit::CEND); 
		return 0;
	}

	/**
	* callback that will run if the sensor value changes by more than the OnSensorChange trigger.
	* @param Index - Index of the output that generated the event
	* @param Value - the sensor read value
	*/
	int CCONV SensorChangeHandler(CPhidgetInterfaceKitHandle IFKH, void *usrptr, int Index, int Value)
	{

		DispatchEventToHaxe( "phidgets.event.IKDataEvent", 
		 	hxpiphidgetinterfacekit::CSTRING,  "ik_data_event_sensor_change",	
			hxpiphidgetinterfacekit::CINT, Index,  
		 	hxpiphidgetinterfacekit::CINT, Value,
		 	hxpiphidgetinterfacekit::CEND); 
		return 0;
	}

	/**
	*
	*/
	void setSensorsChangeTrigger(int value){
		int numSensors, i;
		CPhidgetInterfaceKit_getSensorCount(ifKit, &numSensors);
		for(i = 0; i < numSensors; i++)
		{
			CPhidgetInterfaceKit_setSensorChangeTrigger(ifKit, i, value);
		}
	}

	/**
	*
	*/
	void setSensorChangeTrigger(int channel, int value){
		int numSensors;
		CPhidgetInterfaceKit_getSensorCount(ifKit, &numSensors);
		
		if(channel >= 0 && channel<numSensors-1)
		{
			CPhidgetInterfaceKit_setSensorChangeTrigger(ifKit, channel, value);
		}
	}

	/**
	*
	*/
	void setRatiometric(int value){
		//
		CPhidgetInterfaceKit_setRatiometric(ifKit, value);
	}

	/**
	*
	*/
	void shutdown()
	{
		CPhidget_close((CPhidgetHandle)ifKit);
		CPhidget_delete((CPhidgetHandle)ifKit);
		printf("Releasing Phidhget hardware handles");
	}

	/**
	*
	*/
	void initialize()
	{
		int result, numSensors, i;
		const char *err;

		//create the InterfaceKit object
		CPhidgetInterfaceKit_create(&ifKit);

		//Set the handlers to be run when the device is plugged in or opened from software, unplugged or closed from software, or generates an error.
		CPhidget_set_OnAttach_Handler((CPhidgetHandle)ifKit, AttachHandler, NULL);
		CPhidget_set_OnDetach_Handler((CPhidgetHandle)ifKit, DetachHandler, NULL);
		CPhidget_set_OnError_Handler((CPhidgetHandle)ifKit, ErrorHandler, NULL);

		//Registers a callback that will run if an input changes.
		//Requires the handle for the Phidget, the function that will be called, and an arbitrary pointer that will be supplied to the callback function (may be NULL).
		CPhidgetInterfaceKit_set_OnInputChange_Handler (ifKit, InputChangeHandler, NULL);

		//Registers a callback that will run if the sensor value changes by more than the OnSensorChange trig-ger.
		//Requires the handle for the IntefaceKit, the function that will be called, and an arbitrary pointer that will be supplied to the callback function (may be NULL).
		CPhidgetInterfaceKit_set_OnSensorChange_Handler (ifKit, SensorChangeHandler, NULL);

		//Registers a callback that will run if an output changes.
		//Requires the handle for the Phidget, the function that will be called, and an arbitrary pointer that will be supplied to the callback function (may be NULL).
		CPhidgetInterfaceKit_set_OnOutputChange_Handler (ifKit, OutputChangeHandler, NULL);

		//open the interfacekit for device connections
		CPhidget_open((CPhidgetHandle)ifKit, -1);

		
		if((result = CPhidget_waitForAttachment((CPhidgetHandle)ifKit, 500)))
		{
			CPhidget_getErrorDescription(result, &err);
		}
		
	}
}