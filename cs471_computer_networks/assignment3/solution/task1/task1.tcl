set ns [new Simulator]

set tt_f [open tcptrack.tr w]
set q_f [open queue.tr w]
set g1 [open g1.tr w]
set g2 [open g2.tr w]

set src [$ns node]
set rtr [$ns node]
set dst [$ns node]

$ns duplex-link $src $rtr 2Mb 10ms DropTail
$ns duplex-link $rtr $dst 1Mb 10ms DropTail

$ns queue-limit $src $rtr [expr [expr 279%9] + 4]
$ns queue-limit $rtr $dst [expr [expr 279%9] + 4]

set tcp [new Agent/TCP]
$ns attach-agent $src $tcp
$tcp set packetSize_ 1000

set tcpsink [new Agent/TCPSink]
$ns attach-agent $dst $tcpsink

$ns connect $tcp $tcpsink

set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP

set qm [$ns monitor-queue $rtr $dst $q_f 0.04]
[$ns link $rtr $dst] queue-sample-timeout

$tcp attach $tt_f
$tcp tracevar cwnd_

$ns at 0.01 "$ftp start"
$ns at 0.01 "resetQueue"
$ns at 10.0 "$ftp stop"

$ns at 11.0 "finish"


proc finish {} {
    global ns tt_f
    global ns q_f
    global ns g1
    global ns g2
    $ns flush-trace
    close $tt_f
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
    global ns tcp
    set now [$ns now]
    set cwnd [$tcp set cwnd_]
    set pd [$qm set pdrops_]

    puts $g1 "$now $cwnd"
    puts $g2 "$now $pd"

    $ns at [expr $now+0.04] "plotWindow"
}

$ns at 0.0 "plotWindow"

$ns run
