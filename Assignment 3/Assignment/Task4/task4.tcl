set ns [new Simulator]

# open trace files
set tt_f_1 [open tcptrack1.tr w]
set q_f [open queue.tr w]
set g1 [open g1.tr w]
set g2 [open g2.tr w]

# make nodes
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]

# set links b/w nodes
$ns duplex-link $n1 $n3 2Mb 10ms DropTail
$ns duplex-link $n2 $n3 2Mb 10ms DropTail
$ns duplex-link $n3 $n4 1Mb 10ms DropTail

# set queue limit
$ns queue-limit $n3 $n4 [expr [expr 279%18] + 10]

# tcp conn b/w n1 and n4
set tcp1 [new Agent/TCP]
$ns attach-agent $n1 $tcp1
$tcp1 set packetSize_ 1000

set tcpsink1 [new Agent/TCPSink]
$ns attach-agent $n4 $tcpsink1

$ns connect $tcp1 $tcpsink1

# udp conn b/w n2 and n4
set udp1 [new Agent/UDP]
$ns attach-agent $n2 $udp1

set null1 [new Agent/Null]
$ns attach-agent $n4 $null1

$ns connect $udp1 $null1

# ftp at n1
set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
$ftp1 set type_ FTP

# cbr at n2
set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $udp1
$cbr1 set type_ CBR
$cbr1 set packet_size_ 1000
$cbr1 set rate_ 2mb

# monitor queue
set qm [$ns monitor-queue $n3 $n4 $q_f 0.04]
[$ns link $n3 $n4] queue-sample-timeout

# attach tcp conn with trace files
$tcp1 attach $tt_f_1
$tcp1 tracevar cwnd_

# events
$ns at 0.01 "$ftp1 start"

$ns at 0.01 "resetQueue"

$ns at 5.0 "$cbr1 start"

$ns at 15.0 "$cbr1 stop"
$ns at 20.0 "$ftp1 stop"

$ns at 22.0 "finish"

proc finish {} {
    global ns tt_f_1
    global ns q_f
    global ns g1
    global ns g2

    $ns flush-trace
    close $tt_f_1
    close $q_f
    close $g1
    close $g2
    exec xgraph g1.tr g2.tr -geometry 800x400 &
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
    global ns qm
    global ns tcp1

    set now [$ns now]
    set cwnd1 [$tcp1 set cwnd_]
    set pd [$qm set pdrops_]

    puts $g1 "$now $cwnd1"
    puts $g2 "$now $pd"

    $ns at [expr $now+0.04] "plotWindow" 
}

$ns at 0.0 "plotWindow"
$ns run
