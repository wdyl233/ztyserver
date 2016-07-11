
jQuery(function(){
	Clock();
});
function Clock(){
	var Today=new Date();
	var PPQday=new Date(2013,9-1,29);
	var DayTime = (PPQday.getTime()-Today.getTime())/ 1000 / 60 / 60 /24;
	var days = parseInt(DayTime);//天
	var HourTime =(DayTime - days)*24;
	var hours =parseInt(HourTime);//时
	var MinutesTime =(HourTime-hours)*60;
	var minutes = parseInt(MinutesTime);//分
	var SecondTime =(MinutesTime-minutes)*60;
	var seconds = parseInt(SecondTime);  //秒
	var MillisecondTime = (SecondTime-seconds)*100;//取2位
	var milliseconds = parseInt(MillisecondTime);//毫秒

	document.getElementById("PPQTime").innerHTML= "<span  style=\"margin-left:10px;\">"+ days + "</span><span style=\"margin-left:15px;\">"+ ForMat(hours)+"</span><span style=\"margin-left:12px;\">"+ForMat(minutes)+"</span><span style=\"margin-left:14px;\">"+ForMat(seconds)+"</span>";
	setTimeout(Clock,1000);
}

function ForMat(data){
	if(data<10)
		return "0"+data;
	else
		return data;
}