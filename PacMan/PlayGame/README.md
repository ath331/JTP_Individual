## Game구조(MG = Manager)

	-GameMG가 MapMaker class, CharMG class를 관리한다.
	
	-CharMG는 Character class를 관리한다.
	
		-Character class는 player와 AI에 사용된다.
		
	-MapMaker는 Map관련해서 Update()하고 CharMG는 character들을 Update()한다.
	
	-최종적으로 GameMG에서 Map과 Character를 Draw()한다.
