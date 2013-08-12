$(function(){
    
    $("#link-1").hover(function(){
        switchShield(1);
    });
    $("#link-2").hover(function(){
        switchShield(2);
    });
    $("#link-3").hover(function(){
        switchShield(3);
    });
    $(".img").mouseout(function(){
        switchShield(4);
        $(".link").show();
    });
    
});

function switchShield(p){
    $(".dynamic-show>.img>img").hide();
    $(".dynamic-show>.img>." + p).show();
    
    $(".dynamic-show>.description").hide();
    $(".dynamic-show>.description." + p).show();
}