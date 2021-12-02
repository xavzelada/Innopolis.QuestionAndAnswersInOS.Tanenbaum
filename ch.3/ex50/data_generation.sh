ls -l /usr/local/bin /usr/bin > executables_data.txt
ls -l /usr/local/bin /usr/bin | awk '{count+=$5}END{printf "%f\n",count}' > total.txt
ls -l /usr/local/bin | tail -n +2 | awk '{print $5}' > sizes.txt
ls -l /usr/bin | tail -n +2 | awk '{print $5}' >> sizes.txt
sort -n -o sizes.txt sizes.txt

