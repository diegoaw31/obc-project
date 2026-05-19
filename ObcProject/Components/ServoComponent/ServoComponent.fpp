module ObcProject {
    @ Servomotor c
    active component ServoComponent {

        # One async command/port is required for active components
        # This should be overridden by the developers with a useful command/port

        @ Set servo angle (0–180)
        async command SET_ANGLE(angle: F32)

        ##############################################################################
        #### Uncomment the following examples to start customizing your component ####
        ##############################################################################

        # @ Example async command
        # async command COMMAND_NAME(param_name: U32)

        # @ Example telemetry counter
        # telemetry ExampleCounter: U64
        telemetry Angle: F32

        # @ Example event
        # event ExampleStateEvent(example_state: Fw.On) severity activity high id 0 format "State set to {}"
        event InvalidAngle(angle: F32) severity warning high format "Invalid angle {}"
        event PigpioError(code: I32) severity warning high format "pigpio error {}"
        event AngleSet(angle: F32) severity activity high format "Angle {}"

        # @ Example port: receiving calls from the rate group
        async input port angleIn: ServoAngle

        # @ Example parameter
        # param PARAMETER_NAME: U32

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Enables command handling
        import Fw.Command

        @ Enables event handling
        import Fw.Event

        @ Enables telemetry channels handling
        import Fw.Channel

        @ Port to return the value of a parameter
        param get port prmGetOut

        @Port to set the value of a parameter
        param set port prmSetOut

    }
}