#!/usr/bin/perl -w
#update 2010/09/18 20:04:42
#author @dlqingxi at Tokyo JP
#¼üÅÌi±äÐÎ£¬j×óÒÆ£¬k×¹Âä£¬lÓÒÒÆ

use Term::ReadKey;
use threads;
use threads::shared;
use Switch;

&defineCubes;

my $front_c = "=";
my $backg_c = "~";
my $middle_c = "+";

our $canvas_x = (11 - 1);
our $canvas_y = (16 - 1);
our $canvas;
our $full_lines = 0;
our $debug_info = "You cleared $full_lines lines.";
#init the canvas
for my $_y (0..$canvas_y){
    for my $_x (0..$canvas_x){
        $canvas->[$_y][$_x] = $backg_c;
    }
}

&definePos;
&resetPos;

my $can_use_threads = eval 'use threads; 1';
if($can_use_threads){
    our $ctlkey :shared;
    $ctlkey = "x";
    
    my $thr = threads->create(\&action_listen);
    $thr->detach();
} else {
    print "the thread is not supported.\n";
    exit;
}

&canvas_loop;
sub canvas_loop{
    select (STDOUT);
    $| ++;
    
    while(1){
        &eventHandle;
        if(&allowedAction($cube_nex, $x_nex, $y_nex)){
            &clearNowCube;
            &paintNexCube;
            our $y_nex ++;
        }else {
            &lockNowCube;
            &resetPos;
        }
        
        &displayCanvas($canvas);
#        sleep(1);
        select(undef,undef,undef,0.3);

    }
}

sub displayCanvas{
    my $_ref_cvs = shift;
    my $_dim = $#$_ref_cvs;
    system "cls";
    print "$debug_info \n";
    foreach my $_y (0..$_dim){
        print join('', @{$_ref_cvs->[$_y]})."\n";
    }
}

sub updateCanvas{
    my $_x = shift;
    my $_y = shift;
    my $_canvas = shift;
    $_canvas->[$_y][$_x] = shift;
}

sub defineCubes{
    our @b_0 = ([1,0],[0,1],[1,1],[2,1]);
    our @b_1 = ([2,1],[1,0],[1,1],[1,2]);
    our @b_2 = ([1,2],[2,1],[1,1],[0,1]);
    our @b_3 = ([0,1],[1,2],[1,1],[1,0]);
    
    our @a_0 = ([0,0],[0,1],[0,2],[0,3]);
    our @a_1 = ([2,0],[2,1],[2,2],[2,3]);
    our @a_2 = ([0,0],[0,1],[0,2],[0,3]);
    our @a_3 = ([2,0],[2,1],[2,2],[2,3]);
}

sub definePos{
    our $x_now;
    our $y_now;
    our $x_nex;
    our $y_nex;
    our $cube_now;
    our $cube_nex;
    our $idx;
    
    $idx = 0;
    eval "\$cube_now = \\\@b_".$idx.";";
    $cube_nex = $cube_now;
}

sub resetPos{
    $x_now = $canvas_x /2;
    $y_now = 0;
    $x_nex = $x_now;
    $y_nex = $y_now + 1;
    
    $idx = 0;
    eval "\$cube_now = \\\@b_".$idx.";";
    $cube_nex = $cube_now;
}

sub allowedAction{
    my $cube_obj = shift;
    my $x_0 = shift;
    my $y_0 = shift;
    foreach $_node (@{$cube_obj}){
        my $_x = $_node->[0] + $x_0;
        my $_y = $_node->[1] + $y_0;
        #if bound or filled;
        if($_y > $canvas_y || $_x > $canvas_x || ($canvas->[$_y][$_x] eq $front_c)){
            return 0;
        }
    };
    return 1;
}

sub clearNowCube{
    foreach $_node (@{$cube_now}){
        my $_node_x = $_node->[0] + $x_now;
        my $_node_y = $_node->[1] + $y_now;
        &updateCanvas($_node_x, $_node_y, $canvas, $backg_c);
    }
}

sub paintNexCube{
    foreach $_node (@{$cube_nex}){
        my $_node_x = $_node->[0] + $x_nex;
        my $_node_y = $_node->[1] + $y_nex;
        &updateCanvas($_node_x, $_node_y, $canvas, $middle_c);
    }
    $cube_now = $cube_nex;
    $x_now = $x_nex;
    $y_now = $y_nex;
}

sub lockNowCube{
    if ($y_now == 0){
        print "the app is over.\n";
        exit;
    }
#    my @filled_line = ();
    foreach $_node (@{$cube_now}){
        my $_node_x = $_node->[0] + $x_now;
        my $_node_y = $_node->[1] + $y_now;
        
#        my $_tmp_arr = grep($_ == $_node_y, @filled_line);
#        if($_tmp_arr == 0){
#            
#            push (@filled_line, $_node_y);
#        }
        
        &updateCanvas($_node_x, $_node_y, $canvas, $front_c);
    }
    &displayCanvas($canvas);
#    @filled_line = (sort {$b <=> $a} @filled_line);
    &clearFilledLines;

}

sub clearFilledLines{
    for my $_line (0..$canvas_y) {
    #print $_line;
        if(&isFullFilled($_line)){
            $full_lines ++;
            $debug_info = "You cleared $full_lines lines.";
            #print $_line;
            for my $_y (reverse(1..$_line)){
                for my $_x(0..$canvas_x){
                    $canvas->[$_y][$_x] = $canvas ->[$_y - 1][$_x];
                }
            }
            for my $_x (0..$canvas_x){
                $canvas->[0][$_x] = $backg_c;
            }
        }
    }
#    $debug_info = join (',', @{$_ref_lines});
}

sub isFullFilled{
    my $line_no = shift;
    my $dump_txt = join('', @{$canvas->[$line_no]});

    $dump_txt =~ s/${front_c}//g;
    return $dump_txt eq "";
}

sub action_listen{
    do{{
        ReadMode('cbreak');
        $ctlkey = ReadKey(0);
    }} until $ctlkey =~ /q/;
    exit;
}

sub eventHandle{
    if($ctlkey eq "x"){
        return 0;
    }
    switch ($ctlkey){
        case /^i/ {
            eval "our \$_tst_cube = \\\@b_".(($idx + 1)%4).";";
            if(&allowedAction($_tst_cube, $x_now, $y_now)){
                $idx = ($idx + 1) % 4;
                eval "\$cube_nex = \$_tst_cube;";
                $x_nex = $x_now;
                $y_nex = $y_now;
                &clearNowCube;
                &paintNexCube;
                #&displayCanvas;
                $y_nex ++;
            }
        }
        case /^j/ {
            if(&allowedAction($_tst_cube, $x_now - 1, $y_now)){
                $x_nex = $x_now - 1;
                $y_nex = $y_now;
                &clearNowCube;
                &paintNexCube;
                #&displayCanvas;
                #$y_nex ++;
            }
        ;}
        case /^l/ {
                $x_nex = $x_now + 1;
                $y_nex = $y_now;
                &clearNowCube;
                &paintNexCube;
                #&displayCanvas;
            #    $y_nex ++;
        ;}
        case /^k/ {
                my $tmp_y = $y_now;
                while(&allowedAction($cube_now, $x_now, ++ $tmp_y)){
                    ;
                }
                $y_nex = $tmp_y - 1;
                $x_nex = $x_now;
                &clearNowCube;
                &paintNexCube;
                #&displayCanvas;
        ;}
        else {;}
    }
    $ctlkey = "x";
}