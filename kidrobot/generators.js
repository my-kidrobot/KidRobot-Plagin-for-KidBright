var ADDONS_KIDROBOT_CLASS_BEGIN = 'DEV_I2C1.KidRobot(0, 0x65)';

Blockly.JavaScript['kidrobot_motor'] = function(block) {
	var dropdown_ch = block.getFieldValue('ch');
	var dropdown_dir = block.getFieldValue('dir');
	var value_speed = Blockly.JavaScript.valueToCode(block, 'speed', Blockly.JavaScript.ORDER_ATOMIC);
	var code = ADDONS_KIDROBOT_CLASS_BEGIN + '.motor(' + dropdown_ch + ', ' + dropdown_dir + ', ' + value_speed + ');\n';
	return code;
};

Blockly.JavaScript['kidrobot_motor_forward'] = function(block) {
	var value_speed = Blockly.JavaScript.valueToCode(block, 'speed', Blockly.JavaScript.ORDER_ATOMIC) || '0';
	var code = '';
	code += ADDONS_KIDROBOT_CLASS_BEGIN + '.motor(0, 1, ' + value_speed + ');\t';
	code += ADDONS_KIDROBOT_CLASS_BEGIN + '.motor(1, 0, ' + value_speed + ');\n';
	return code;
};

Blockly.JavaScript['kidrobot_motor_backward'] = function(block) {
	var value_speed = Blockly.JavaScript.valueToCode(block, 'speed', Blockly.JavaScript.ORDER_ATOMIC) || '0';
	var code = '';
	code += ADDONS_KIDROBOT_CLASS_BEGIN + '.motor(0, 0, ' + value_speed + ');\t';
	code += ADDONS_KIDROBOT_CLASS_BEGIN + '.motor(1, 1, ' + value_speed + ');\n';
	return code;
};

Blockly.JavaScript['kidrobot_motor_turn_left'] = function(block) {
	var value_speed = Blockly.JavaScript.valueToCode(block, 'speed', Blockly.JavaScript.ORDER_ATOMIC) || '0';
	var code = '';
	code += ADDONS_KIDROBOT_CLASS_BEGIN + '.motor(0, 0, 0);\t';
	code += ADDONS_KIDROBOT_CLASS_BEGIN + '.motor(1, 0, ' + value_speed + ');\n';
	return code;
};

Blockly.JavaScript['kidrobot_motor_turn_right'] = function(block) {
	var value_speed = Blockly.JavaScript.valueToCode(block, 'speed', Blockly.JavaScript.ORDER_ATOMIC) || '0';
	var code = '';
	code += ADDONS_KIDROBOT_CLASS_BEGIN + '.motor(0, 1, ' + value_speed + ');\t';
	code += ADDONS_KIDROBOT_CLASS_BEGIN + '.motor(1, 0, 0);\n';
	return code;
};

Blockly.JavaScript['kidrobot_motor_spin_left'] = function(block) {
	var value_speed = Blockly.JavaScript.valueToCode(block, 'speed', Blockly.JavaScript.ORDER_ATOMIC) || '0';
	var code = '';
	code += ADDONS_KIDROBOT_CLASS_BEGIN + '.motor(0, 1, ' + value_speed + ');\t';
	code += ADDONS_KIDROBOT_CLASS_BEGIN + '.motor(1, 0, ' + value_speed + ');\n';
	return code;
};

Blockly.JavaScript['kidrobot_motor_spin_right'] = function(block) {
	var value_speed = Blockly.JavaScript.valueToCode(block, 'speed', Blockly.JavaScript.ORDER_ATOMIC) || '0';
	var code = '';
	code += ADDONS_KIDROBOT_CLASS_BEGIN + '.motor(0, 0, ' + value_speed + ');\t';
	code += ADDONS_KIDROBOT_CLASS_BEGIN + '.motor(1, 1, ' + value_speed + ');\n';
	return code;
};

Blockly.JavaScript['kidrobot_motor_stop'] = function(block) {
	var code = '';
	code += ADDONS_KIDROBOT_CLASS_BEGIN + '.motor(0, 0, 0);\t';
	code += ADDONS_KIDROBOT_CLASS_BEGIN + '.motor(1, 0, 0);\n';
	return code;
};

Blockly.JavaScript['kidrobot_motor_forward2'] = function(block) {
	var value_speed1 = Blockly.JavaScript.valueToCode(block, 'speed1', Blockly.JavaScript.ORDER_ATOMIC) || '0';
	var value_speed2 = Blockly.JavaScript.valueToCode(block, 'speed2', Blockly.JavaScript.ORDER_ATOMIC) || '0';
	var code = '';
	code += ADDONS_KIDROBOT_CLASS_BEGIN + '.motor(0, 1, ' + value_speed1 + ');\t';
	code += ADDONS_KIDROBOT_CLASS_BEGIN + '.motor(1, 0, ' + value_speed2 + ');\n';
	return code;
};

Blockly.JavaScript['kidrobot_motor_backward2'] = function(block) {
	var value_speed1 = Blockly.JavaScript.valueToCode(block, 'speed1', Blockly.JavaScript.ORDER_ATOMIC) || '0';
	var value_speed2 = Blockly.JavaScript.valueToCode(block, 'speed2', Blockly.JavaScript.ORDER_ATOMIC) || '0';
	var code = '';
	code += ADDONS_KIDROBOT_CLASS_BEGIN + '.motor(1, 0, ' + value_speed1 + ');\t';
	code += ADDONS_KIDROBOT_CLASS_BEGIN + '.motor(0, 1, ' + value_speed2 + ');\n';
	return code;
};

