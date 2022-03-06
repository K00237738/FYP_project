print("Hello world!")

def timeLoop():
	timeTotal = h * 3600#max will be set to an hour
	minuteMark = 0
	
	while(timeTotal>0):
		time.sleep(1)#sleep for one second
		timeTotal-=1#decrtement 1 second
		minuteMark+=1
		if(minuteMark==60)
		{//every minute, call request
			#make call
			minuteMark=0
		}
	#end loop