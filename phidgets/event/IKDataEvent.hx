package phidgets.event;
import openfl.events.Event;

class IKDataEvent extends Event
{
    public static inline var INPUT_CHANGE  = "ikevent_input_change";
    public static inline var OUTPUT_CHANGE = "ikevent_output_change";
    public static inline var SENSOR_CHANGE = "ikevent_sensor_change";

    public var channel(default, null) : Int;
 	public var value(default, null) : Int;

    public function new(type:String, channel:Int, value:Int)
    {
        super(type, true, true);
        this.channel = channel;
        this.value   = value;
    }

	public override function clone() : Event
    {
		return new IKDataEvent(type, channel, value);
	}

	public override function toString() : String
    {
        var s = "[IKDataEvent type=" + type + " channel=" + channel + ", value=" + value+ "]";
        return s;
	}
}