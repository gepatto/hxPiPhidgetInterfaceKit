package phidgets;

import openfl.events.Event;
import openfl.events.IEventDispatcher;
import phidgets.event.IKEvent;
import openfl.display.Sprite;
import openfl.display.Stage;
import haxe.Json;

#if cpp
import cpp.Lib;
#elseif neko
import neko.Lib;
#end


class PhidgetInterfaceKit {
	
	private static var s_initialized:Bool = false;
	private static var hxpiphidgetinterfacekit_set_haxe_callback_for_dispatching_events = null;
	private static var s_nextEventDispatcherId:Int = 1;
	private static var s_eventDispatcherMap:Map<Int, IEventDispatcher> = new Map<Int, IEventDispatcher>();
 	public static var stage(get, never) : Stage;

 	/**
 	*
 	*/
	public static function initialize():Void{
		
		if(s_initialized) return;
		
		hxpiphidgetinterfacekit_set_haxe_callback_for_dispatching_events = Lib.load("hxPiPhidgetInterfaceKit", "hxpiphidgetinterfacekit_set_haxe_callback_for_dispatching_events", 1);
		hxpiphidgetinterfacekit_set_haxe_callback_for_dispatching_events(CreateAndDispatchEvent);

		hxpiphidgetinterfacekit_initialize();
		s_initialized = true;
	
		stage.dispatchEvent(new IKEvent( IKEvent.LIB_INIT, "Library Initialized" ,0 ));
	}
	private static var hxpiphidgetinterfacekit_initialize = Lib.load ("hxPiPhidgetInterfaceKit", "hxpiphidgetinterfacekit_initialize", 0);

	/**
 	*
 	*/
	public static function shutdown():Void{
		hxpiphidgetinterfacekit_shutdown();
	}
	private static var hxpiphidgetinterfacekit_shutdown = Lib.load ("hxPiPhidgetInterfaceKit", "hxpiphidgetinterfacekit_shutdown", 0);	

	/**
 	* Set one
 	*/
	public static function setSensorChangeTrigger( channel:Int, value:Int ):Void{
		hxpiphidgetinterfacekit_setSensorChangeTrigger(channel,value);
	}
	private static var hxpiphidgetinterfacekit_setSensorChangeTrigger = Lib.load ("hxPiPhidgetInterfaceKit", "hxpiphidgetinterfacekit_setSensorChangeTrigger", 2);

	/**
 	* Set All
 	*/
	public static function setSensorsChangeTrigger( value:Int ):Void{
		hxpiphidgetinterfacekit_setSensorsChangeTrigger(value);
	}
	private static var hxpiphidgetinterfacekit_setSensorsChangeTrigger = Lib.load ("hxPiPhidgetInterfaceKit", "hxpiphidgetinterfacekit_setSensorsChangeTrigger", 1);

	/**
 	*
 	*/
	public static function RegisterEventDispatcher(obj:IEventDispatcher) : Int
	{

		var id = s_nextEventDispatcherId++;
		s_eventDispatcherMap.set(id, obj);
		trace("RegisterEventDispatcher: " + id);
		return id;
	}
	
	public static function UnregisterEventDispatcher(eventDispatcherId:Int) : Void
	{
		s_eventDispatcherMap.remove(eventDispatcherId);
	}


	/**
     * Creates an event object from the specific package & class spec, and constructor
     * arguments. Then, dispatches the event on the stage.
     */
    private static function CreateAndDispatchEvent(eventDispatcherId:Int, eventPackageAndClass:String, args:Array<Dynamic>) : Void
    {
       // TraceEvent(eventPackageAndClass, args);
      
        var eventClass = Type.resolveClass(eventPackageAndClass);
        if (eventClass == null)
        {
            trace("[ERROR] Unable to find event class '" + eventPackageAndClass + "'");
            return;
        }

        var event = Type.createInstance(eventClass, args);
        if (event == null)
        {
            trace("[ERROR] Unable to instantiate event class '" + eventPackageAndClass + "'");
            return;
        }


		var target:IEventDispatcher = stage;
		if (eventDispatcherId > 0)
		{
			var newtarget:IEventDispatcher = s_eventDispatcherMap.get(eventDispatcherId);
			if (newtarget != null)
			{
				target = newtarget;
	
			}
		}

		target.dispatchEvent(event);
		
    }

	/**
 	*
 	*/
	private static function TraceEvent(eventPackageAndClass:String, args:Array<Dynamic>) : Void
    {
        var sb:StringBuf = new StringBuf();
        var a = [];
        sb.add("Dispatching event ");
        sb.add(eventPackageAndClass);
        sb.add("(");
        for (p in args)
        {
            if (Std.is(p, String))
            {
                a.push("\"" + p + "\"");
            }
            else
            {
                a.push(p);
            }
        }
        sb.add(a.join(", "));
        sb.add(")");
        trace(sb.toString());
    }
    
	/**
 	*
 	*/
    private static function get_stage() : Stage
    {
        return openfl.Lib.current.stage;
    }
}