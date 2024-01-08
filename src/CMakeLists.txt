cmake_minimum_required (VERSION 3.26)
project ("SDL2_Game1")

add_executable (
	SDL2_Game1 
	"Main.cpp" 
	"Application.cpp" 
	"Scenes.cpp" 
	"Player.cpp" 
	"Boss.cpp" 
	"FireBall.cpp"  
	"FirePillar.h" 
	"FirePillar.cpp" 
	"Camera.cpp" 
	"Ui.h" 
	"Ui.cpp" 
	"Base.h" 
	"Base.cpp" 
	"Audio.cpp"
)