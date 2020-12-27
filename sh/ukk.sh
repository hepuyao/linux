#/bin/bash 
while ((1))
do
	gsettings set org.ukui.control-center.personalise transparency 0.1
	gsettings set org.ukui.control-center.personalise transparency 0.2
	gsettings set org.ukui.control-center.personalise transparency 0.3
	gsettings set org.ukui.control-center.personalise transparency 0.4
	gsettings set org.ukui.control-center.personalise transparency 0.5
	gsettings set org.ukui.control-center.personalise transparency 0.6
	gsettings set org.ukui.control-center.personalise transparency 0.7
	gsettings set org.ukui.control-center.personalise transparency 0.8
	gsettings set org.ukui.control-center.personalise transparency 0.9
	gsettings set org.ukui.control-center.personalise transparency 1
	killall ukui-panel
done
