## Game구조(MG = Manager)

	-GameMG가 MapMaker class, CharMG class를 관리한다.
	
	-CharMG는 Character class를 관리한다.
	
		-Character class는 player와 AI에 사용된다.
		
	-MapMaker는 Map관련해서 Draw()하고 CharMG는 charcter들을 Update()한다.
	
	-Update()된 charcter들을 GameMG가 Draw()한다.
