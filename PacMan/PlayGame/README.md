## Game구조(MG = Manager)

	-GameMG가 MapMaker class, CharMG class를 관리한다.
	
	-CharMG는 Character class를 관리한다.
	
		-Character class는 player와 AI에 사용된다.
		
	-MapMaker는 Map관련해서 Update(),Draw()하고 CharMG는 character들을 Update(),Draw()한다.
	
	-최종적으로 GameMG에서 Map과 Character를 Draw()한다.
	
	-Map을 먼저 Draw() 그 위에 Chacter를 Draw()하는 방식.
		
		- 커서 이동 함수를 이용하여 캐릭터의 변한 위치로 커서를 이동해서 캐릭터를 Draw()한다.
