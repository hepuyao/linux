#/bin/bash 
while ((1))
do
        gsettings set org.ukui.control-center.personalise transparency 0.1
	sleep  0.03
        gsettings set org.ukui.control-center.personalise transparency 0.2
	sleep 0.01
        gsettings set org.ukui.control-center.personalise transparency 0.3
	sleep 0.01
	gsettings set org.ukui.control-center.personalise transparency 0.4
        sleep 0.01
        gsettings set org.ukui.control-center.personalise transparency 0.5
	sleep 0.01
	gsettings set org.ukui.control-center.personalise transparency 0.6
        sleep 0.01
	gsettings set org.ukui.control-center.personalise transparency 0.7
        sleep 0.02
        gsettings set org.ukui.control-center.personalise transparency 0.8
	sleep 0.01
        gsettings set org.ukui.control-center.personalise transparency 0.9
	gsettings set org.ukui.control-center.personalise transparency 1
        sleep 0.01
done

