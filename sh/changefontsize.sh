#/bin/bash 
while ((1))
do
        for((i=11;i<=16;i++));
	do
        	sleep 1
		s="Noto Sans CJK SC  ${i}";
		echo $s
        	gsettings set org.ukui.style system-font-size $i
        	gsettings set org.mate.interface font-name  "$s"
        	gsettings set org.gnome.desktop.wm.preferences titlebar-font  "$s"
        	gsettings set org.mate.interface document-font-name  "$s"
	done
done

