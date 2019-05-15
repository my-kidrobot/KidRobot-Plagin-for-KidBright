Blockly.Blocks['kidrobot_ultrasonic'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.KIDROBOT_ULTRASONIC_MESSAGE,
			"output": "Number",
			"colour": 180,
			"tooltip": Blockly.Msg.KIDROBOT_ULTRASONIC_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['kidrobot_line_sensor'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.KIDROBOT_LINE_SENSOR_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "ch",
				"options": [
					[ Blockly.Msg.KIDROBOT_LINE_SENSOR_LEFTSIDE_MESSAGE, "1" ],
					[ Blockly.Msg.KIDROBOT_LINE_SENSOR_RIGHTSIDE_MESSAGE, "2" ],
					[ Blockly.Msg.KIDROBOT_LINE_SENSOR_ALL_MESSAGE, "3" ],
					[ Blockly.Msg.KIDROBOT_LINE_SENSOR_NONE_MESSAGE, "4" ]
				]
			}, {
				"type": "field_dropdown",
				"name": "color",
				"options": [
					[ Blockly.Msg.KIDROBOT_LINE_SENSOR_BLACK_MESSAGE, "1" ],
					[ Blockly.Msg.KIDROBOT_LINE_SENSOR_WHITE_MESSAGE, "2" ]
				]
			}],
			"output": [
				"Number",
				"Boolean"
			],
			"colour": 180,
			"tooltip": Blockly.Msg.KIDROBOT_LINE_SENSOR_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['kidrobot_ir_sensor'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.KIDROBOT_IR_SENSOR_MESSAGE,
			"output": "Number",
			"colour": 180,
			"tooltip": Blockly.Msg.KIDROBOT_IR_SENSOR_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['kidrobot_led'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.KIDROBOT_LED_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "n",
				"options": [
					[ "1", "1" ],
					[ "2", "2" ],
					[ "3", "3" ],
					[ "4", "4" ]
				]
			}, {
			  "type": "field_colour",
			  "name": "color",
			  "colour": "#ff0000"
			}],
			"previousStatement": null,
			"nextStatement": null,
			"colour": 180,
			"tooltip": Blockly.Msg.KIDROBOT_LED_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['kidrobot_motor_forward'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.KIDROBOT_MOTOR_FORWARD_MESSAGE,
			"args0": [{
				"type": "field_image",
				"src": "https://a.lnwpic.com/4p6j61.png",
				"width": 18,
				"height": 16,
				"alt": "*",
				"flipRtl": false
			}, {
				"type": "input_value",
				"name": "speed",
				"check": "Number"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 180,
			"tooltip": Blockly.Msg.KIDROBOT_MOTOR_FORWARD_TOOLTIP,
			"helpUrl": "https://store.kidbright.info/plugin/7/iKB-1"
		});
	}
};

Blockly.Blocks['kidrobot_motor_backward'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.KIDROBOT_MOTOR_BACKWARD_MESSAGE,
			"args0": [{
				"type": "field_image",
				"src": "https://a.lnwpic.com/4p6j61.png",
				"width": 20,
				"height": 16,
				"alt": "*",
				"flipRtl": false
			}, {
				"type": "input_value",
				"name": "speed",
				"check": "Number"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 180,
			"tooltip": Blockly.Msg.KIDROBOT_MOTOR_BACKWARD_TOOLTIP,
			"helpUrl": "https://store.kidbright.info/plugin/7/iKB-1"
		});
	}
};

Blockly.Blocks['kidrobot_motor_forward2'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.KIDROBOT_MOTOR_FORWARD_2_MESSAGE,
			"args0": [{
				"type": "field_image",
				"src": "https://a.lnwpic.com/4p6j61.png",
				"width": 18,
				"height": 16,
				"alt": "*",
				"flipRtl": false
			}, {
				"type": "input_value",
				"name": "speed1",
				"check": "Number"
			}, {
				"type": "input_value",
				"name": "speed2",
				"check": "Number"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 180,
			"tooltip": Blockly.Msg.KIDROBOT_MOTOR_FORWARD_2_TOOLTIP,
			"helpUrl": "https://store.kidbright.info/plugin/7/iKB-1"
		});
	}
};

Blockly.Blocks['kidrobot_motor_backward2'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.KIDROBOT_MOTOR_BACKWARD_2_MESSAGE,
			"args0": [{
				"type": "field_image",
				"src": "https://a.lnwpic.com/4p6j61.png",
				"width": 18,
				"height": 16,
				"alt": "*",
				"flipRtl": false
			}, {
				"type": "input_value",
				"name": "speed1",
				"check": "Number"
			}, {
				"type": "input_value",
				"name": "speed2",
				"check": "Number"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 180,
			"tooltip": Blockly.Msg.KIDROBOT_MOTOR_BACKWARD_2_TOOLTIP,
			"helpUrl": "https://store.kidbright.info/plugin/7/iKB-1"
		});
	}
};

Blockly.Blocks['kidrobot_motor_turn_left'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.KIDROBOT_MOTOR_TRUE_LEFT_MESSAGE,
			"args0": [{
				"type": "field_image",
				"src": "https://a.lnwpic.com/4p6j61.png",
				"width": 18,
				"height": 16,
				"alt": "*",
				"flipRtl": false
			}, {
				"type": "input_value",
				"name": "speed",
				"check": "Number"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 180,
			"tooltip": Blockly.Msg.KIDROBOT_MOTOR_TRUE_LEFT_TOOLTIP,
			"helpUrl": "https://store.kidbright.info/plugin/7/iKB-1"
		});
	}
};

Blockly.Blocks['kidrobot_motor_turn_right'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.KIDROBOT_MOTOR_TRUE_RIGHT_MESSAGE,
			"args0": [{
				"type": "field_image",
				"src": "https://a.lnwpic.com/4p6j61.png",
				"width": 18,
				"height": 16,
				"alt": "*",
				"flipRtl": false
			}, {
				"type": "input_value",
				"name": "speed",
				"check": "Number"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 180,
			"tooltip": Blockly.Msg.KIDROBOT_MOTOR_TRUE_RIGHT_TOOLTIP,
			"helpUrl": "https://store.kidbright.info/plugin/7/iKB-1"
		});
	}
};

Blockly.Blocks['kidrobot_motor_spin_left'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.KIDROBOT_MOTOR_SPIN_LEFT_MESSAGE,
			"args0": [{
				"type": "field_image",
				"src": "https://a.lnwpic.com/4p6j61.png",
				"width": 18,
				"height": 16,
				"alt": "*",
				"flipRtl": false
			}, {
				"type": "input_value",
				"name": "speed",
				"check": "Number"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 180,
			"tooltip": Blockly.Msg.KIDROBOT_MOTOR_SPIN_LEFT_TOOLTIP,
			"helpUrl": "https://store.kidbright.info/plugin/7/iKB-1"
		});
	}
};

Blockly.Blocks['kidrobot_motor_spin_right'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.KIDROBOT_MOTOR_SPEN_RIGHT_MESSAGE,
			"args0": [{
				"type": "field_image",
				"src": "https://a.lnwpic.com/4p6j61.png",
				"width": 18,
				"height": 16,
				"alt": "*",
				"flipRtl": false
			}, {
				"type": "input_value",
				"name": "speed",
				"check": "Number"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 180,
			"tooltip": Blockly.Msg.KIDROBOT_MOTOR_SPEN_RIGHT_TOOLTIP,
			"helpUrl": "https://store.kidbright.info/plugin/7/iKB-1"
		});
	}
};

Blockly.Blocks['kidrobot_motor_stop'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.KIDROBOT_MOTOR_STOP_MESSAGE,
			"args0": [{
				"type": "field_image",
				"src": "https://a.lnwpic.com/4p6j61.png",
				"width": 18,
				"height": 16,
				"alt": "*",
				"flipRtl": false
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 180,
			"tooltip": Blockly.Msg.KIDROBOT_MOTOR_STOP_TOOLTIP,
			"helpUrl": "https://store.kidbright.info/plugin/7/iKB-1"
		});
	}
};
