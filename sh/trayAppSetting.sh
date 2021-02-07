#bash
for((i=0;i<20;i++))
do
	echo $i
	s="org.ukui.panel.tray:/org/ukui/tray/keybindings/custom${i}/";
	gsettings get  "$s" name
done

