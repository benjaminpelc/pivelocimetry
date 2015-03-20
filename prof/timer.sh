#!/usr/bin/env zsh

runNo=0
noRuns=$1
# (time ../bin/bppiv) 2>&1 | awk '{split($0, a, " "); print a[8]}'
# a=$((time ../bin/bppiv) 2>&1 | awk '{split($0, a, " "); print a[8]}')
# echo $a
average=0.0
while [[ $runNo -lt $noRuns ]];do
	
	let runNo=$runNo+1
	# echo $runNo
	b[$runNo]=$((time ../bin/bppiv) 2>&1 | awk '{split($0, a, " "); print a[8]}')


	# echo ${b[runNo]}
	let average=$average+${b[runNo]}
	# echo $average
	printf "Run %d:\t%0.3f\t Total:\t%0.3f\n" $runNo ${b[runNo]} $average
done

let average=$average/$runNo

printf "%d run average:\t%0.3f\n" $runNo $average

# do
# # b[$runNo]=$((time ../bin/bppiv) 2>&1 | awk '{split($0, a, " "); print a[8]}')
# b[1]=$runNo
# ##b[1]=($a)
#
# # echo $a
# echo ${b[1]}
# runNo=$runNo+1
# # (time ../bin/bppiv) 3>&1 | awk '{split($0, ls, "\n"); print a[1]}'
# done
#
