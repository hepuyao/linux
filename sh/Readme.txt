查看某个进程的详细
pidof ukui-panel |awk '{for(i=1;i<=NF;i++){ printf $i; if(i!=NF) printf ",";}}' |xargs mate-terminal -x top -p
