
#ifndef HXPIPHIDGETINTERFACEKIT_H
#define HXPIPHIDGETINTERFACEKIT_H


namespace hxpiphidgetinterfacekit {
	
	enum
    {
        CEND,
        CSTRING,
        CINT,
        CDOUBLE
    };

    void DispatchEventToHaxe(const char* eventClassSpec, ...);
	void DispatchEventToHaxeInstance(int eventDispatcherId, const char* eventClassSpec, ...);
    
    AutoGCRoot* GetHaxeCallbackForDispatchingEvents();
    void SetHaxeCallbackForDispatchingEvents(AutoGCRoot* haxeCallback);
	void InvokeHaxeCallbackFunctionForDispatchingEvents(int eventDispatcherId, const char* eventClassSpec, va_list params);

    void initialize();
    void shutdown();
	
    void setSensorChangeTrigger(int channel, int value );
    void setSensorsChangeTrigger(int value );
    void setRatiometric(int value);
	
}

#endif