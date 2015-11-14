package phidgets.event;
import openfl.events.Event;

class IKEvent extends Event
{
	public static inline var LIB_INIT  	   = "ikevent_initialized";
    public static inline var DEVICE_ATTACH = "ikevent_device_attach";
    public static inline var DEVICE_DETACH = "ikevent_device_detach";

 	public var data(default, null) : String = null;
    public var devicename(default, null) : String;
    public var serialno(default, null) : Int;

    public function new(type:String,  devicename:String, serialno:Int)
    {
        super(type, true, true);
        this.devicename = devicename;
        this.serialno = serialno;
    }

	public override function clone() : Event
    {
		return new IKEvent(type,  this.devicename, this.serialno);
	}

	public override function toString() : String
    {
        var s = "[IKEvent type=" + type + " devicename=" + this.devicename + " serialno=" + this.serialno  ;
        return s;
	}
}