#/bin/bash 
while ((1))
do
	for((i=1;i<=10;i++));
do
	sleep 0.1
	s=0.`scale=2 expr $i % 10 `;
	gsettings set org.ukui.control-center.personalise transparency $s
	gsettings set org.ukui.style peony-side-bar-transparency `expr $i \* 10`
	gsettings set org.ukui.style menu-transparency `expr $i \* 10`
done
done

