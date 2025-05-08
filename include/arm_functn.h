void torqueEnable(){
    st.writeByte(SERVO_1_ID, SMS_STS_TORQUE_ENABLE, 1);  // Enable torque for servo 12
    st.writeByte(SERVO_2_ID, SMS_STS_TORQUE_ENABLE, 1);  // Enable torque for servo 13
    st.writeByte(SERVO_0_ID, SMS_STS_TORQUE_ENABLE, 1);
    st.writeByte(SERVO_3_ID, SMS_STS_TORQUE_ENABLE, 1);
    st.writeByte(SERVO_4_ID, SMS_STS_TORQUE_ENABLE, 1);
    st.writeByte(SERVO_5_ID, SMS_STS_TORQUE_ENABLE, 1);
}
void torqueDisable(){
    st.writeByte(SERVO_1_ID, SMS_STS_TORQUE_ENABLE, 0);  // Enable torque for servo 12
    st.writeByte(SERVO_2_ID, SMS_STS_TORQUE_ENABLE, 0);  // Enable torque for servo 13
    st.writeByte(SERVO_0_ID, SMS_STS_TORQUE_ENABLE, 0);
    st.writeByte(SERVO_3_ID, SMS_STS_TORQUE_ENABLE, 0);
    st.writeByte(SERVO_4_ID, SMS_STS_TORQUE_ENABLE, 0);
    st.writeByte(SERVO_5_ID, SMS_STS_TORQUE_ENABLE, 0);
}
