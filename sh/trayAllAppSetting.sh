#!/bin/bash
#for((i=0;i<20;i++))
for i in `seq 20`
do
	echo $i
	s="org.ukui.panel.tray:/org/ukui/tray/keybindings/custom${i}/";
	#gsettings get  "$s" name
	gsettingGetAppName=$(gsettings get  "$s" name);
	trayAppName=\'explorer.exe\'
	echo $gsettingGetAppName
	echo $trayAppName
		gsettings set org.ukui.panel.tray:/org/ukui/tray/keybindings/custom${i}/ action storage
		 gsettings set org.ukui.panel.tray:/org/ukui/tray/keybindings/custom${i}/ record storage
done

