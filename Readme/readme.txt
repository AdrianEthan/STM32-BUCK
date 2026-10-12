
目前需要弄懂的东西：

①：TIM2/TIM3/TIM4三个定时器的功能


②：AliIoT_Parameter_Init();
这个函数功能是初始化  三段码和连接阿里云的IP和端口号这些参数

连接阿里云服务器在wifi.c中   第107行
WiFi_printf("AT+CIPSTART=\"TCP\",\"%s\",%d\r\n",ServerIP,ServerPort);//发送连接服务器指令

这时候的 ServerIP和ServerPort应该是已经经过处理了
③点亮LED灯

if(MQTT_CMDOutPtr != MQTT_CMDInPtr){                             //if成立的话，说明命令缓冲区有数据了			       
				u1_printf("命令:%s\r\n",&MQTT_CMDOutPtr[2]);                 //串口输出信息
				if(strstr((char *)MQTT_CMDOutPtr+2,"\params\":{\"PowerSwitch\":1}")){
        LED1_ON;
        LED1_State();
        }else if(strstr((char *)MQTT_CMDOutPtr+2,"\params\":{\"PowerSwitch\":0}")){
        LED1_OFF;
        LED1_State();
        }
				 MQTT_CMDOutPtr += BUFF_UNIT;                             	 //指针下移
				  if(MQTT_CMDOutPtr==MQTT_CMDEndPtr)           	             //如果指针到缓冲区尾部了
					MQTT_CMDOutPtr = MQTT_CMDBuf[0];          	             //指针归位到缓冲区开头			

