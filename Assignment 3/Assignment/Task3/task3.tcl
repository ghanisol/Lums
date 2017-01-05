set ns [new Simulator]

# open trace files
set tt_f_1 [open tcptrack1.tr w]
set tt_f_2 [open tcptrack2.tr w]
set tt_f_3 [open tcptrack3.tr w]
set q_f [open queue.tr w]
set g1 [open g1.tr w]
set g2 [open g2.tr w]
set g3 [open g3.tr w]
set g4 [open g4.tr w]

# make nodes
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]

# set links b/w nodes
$ns duplex-link $n1 $n3 2Mb 10ms DropTail
$ns duplex-link $n2 $n3 2Mb 10ms DropTail
$ns duplex-link $n3 $n4 1Mb 10ms DropTail

#set queue limit
$ns queue-limit $n3 $n4 [expr [expr 279%10] + 35]

# tcp conn b/w n1 and n4
set tcp1 [new Agent/TCP]
$ns attach-agent $n1 $tcp1
$tcp1 set packetSize_ 1000

set tcpsink1 [new Agent/TCPSink]
$ns attach-agent $n4 $tcpsink1

$ns connect $tcp1 $tcpsink1

# tcp conn b/w n2 and n4
set tcp2 [new Agent/TCP]
$ns attach-agent $n2 $tcp2
$tcp2 set packetSize_ 1000

set tcpsink2 [new Agent/TCPSink]
$ns attach-agent $n4 $tcpsink2

$ns connect $tcp2 $tcpsink2

# 2nd tcp conn b/w n1 and n4
set tcp3 [new Agent/TCP]
$ns attach-agent $n1 $tcp3
$tcp3 set packetSize_ 1000

set tcpsink3 [new Agent/TCPSink]
$ns attach-agent $n4 $tcpsink3

$ns connect $tcp3 $tcpsink3

# ftp at n1
set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
$ftp1 set type_ FTP

# ftp at n1
set ftp3 [new Application/FTP]
$ftp3 attach-agent $tcp3
$ftp3 set type_ FTP

# ftp at n2
set ftp2 [new Application/FTP]
$ftp2 attach-agent $tcp2
$ftp2 set type_ FTP

# monitor queue
set qm [$ns monitor-queue $n3 $n4 $q_f 0.04]
[$ns link $n3 $n4] queue-sample-timeout

# attach tcp conn with trace files
$tcp1 attach $tt_f_1
$tcp1 tracevar cwnd_

$tcp2 attach $tt_f_2
$tcp2 tracevar cwnd_

$tcp3 attach $tt_f_3
$tcp3 tracevar cwnd_

# events
$ns at 0.01 "$ftp1 start"
$ns at 0.01 "$ftp2 start"
$ns at 0.01 "$ftp3 start"

$ns at 0.01 "resetQueue"

$ns at 10.0 "$ftp1 stop"
$ns at 10.0 "$ftp2 stop"
$ns at 10.0 "$ftp3 stop"

$ns at 11.0 "finish"

proc finish {} {
    global ns tt_f_1
    global ns tt_f_2
    global ns tt_f_3
    global ns q_f
    global ns g1
    global ns g2
    global ns g3
    global ns g4

    $ns flush-trace
    close $tt_f_1
    close $tt_f_2
    close $tt_f_3
    close $q_f
    close $g1
    close $g2
    close $g3
    close $g4
 
    exec xgraph g1.tr g2.tr g3.tr g4.tr -geometry 800x400 &
    exit 0
}

proc resetQueue {} {
    global ns qm
    $qm reset
    set now [$ns now]
    $ns at [expr $now + 0.04] "resetQueue"
}

proc plotWindow {} {
    global ns g1
    global ns g2
    global ns g3
    global ns g4
    global ns qm
    global ns tcp1
    global ns tcp3
    global ns tcp2

   set now [$ns now]
   set cwnd1 [$tcp1 set cwnd_]
   set cwnd2 [$tcp3 set cwnd_]
   set cwnd3 [$tcp2 set cwnd_]
   set pd [$qm set pdrops_]

   puts $g1 "$now $cwnd1"
   puts $g2 "$now $cwnd2"
   puts $g3 "$now $cwnd3"
   puts $g4 "$now $pd"

   $ns at [expr $now+0.04] "plotWindow"
}

$ns at 0.0 "plotWindow"

$ns run
