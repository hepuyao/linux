#!/bin/bash
while((i<30))
do
	for((i=1;i<=5;i++));  
do   
	peony &
	sleep 3
done  
	kylin-video &
	sleep 4
	ukui-control-center &
	sleep 10
	ukui-clock &
	sleep 4
	ukui-about &
	sleep 3
	ubuntu-kylin-software-center &
	sleep 10

	killall peony 
       	killall kylin-video 
       	killall ukui-control-center 
       	killall ukui-clock 
       	killall ukui-about 
       	killall ubuntu-kylin-software-center  
	killall mate-terminal
done
	
