#include <raylib.h>

class Player {
	Vector2 position;
	int score;
	int speed;
	public:
		Player(Vector2 position, int score, int speed) {
			this->position = position;
			this->score = score;
			this->speed = speed;
		}
		Vector2 getPosition() {
			return position;
		}
		int getScore() {
			return score;
		}
		void setPosition(Vector2 position) {
			this->position = position;
		}
		void setScore(int score) {
			this->score = score;
		}
		void draw() {
			DrawRectangle(position.x, position.y, 20, 100, WHITE);
		}
		void update() {
			draw();
		}
		int getSpeed() {
			return speed;
		}
};
class Ball {
	Vector2 speed;
	Vector2 position;
	public:
		Ball(Vector2 speed, Vector2 position) {
			this->speed = speed;
			this->position = position;
		}
		Vector2 getSpeed() {
			return speed;
		}
		Vector2 getPosition() {
			return position;
		}
		void setSpeed(Vector2 speed) {
			this->speed = speed;
		}
		void setPosition(Vector2 position) {
			this->position = position;
		}
		void draw() {
			DrawCircle((float)position.x, (float)position.y, 10, WHITE);
		}
		void update() {
			draw();
		}
};

int main(void){
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;
	InitWindow(screenWidth, screenHeight, "Pong");
	
	Player player1 = Player({ 20, 200 }, 0,5);
	Player player2 = Player({ 760, 200 }, 0,5);
	Ball ball = Ball({0,0}, {400, 225});
	int player1Score = 0;
	int player2Score = 0;
	bool gameOver = false;
	bool pause = false;
	bool start = false;

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while(!WindowShouldClose()){

		// Update
		//----------------------------------------------------------------------------------
		if (IsKeyDown(KEY_W)) {
			player1.setPosition({ player1.getPosition().x, player1.getPosition().y - player1.getSpeed()});
			player1.update();
		}
		if (IsKeyDown(KEY_S)) {
			player1.setPosition({ player1.getPosition().x, player1.getPosition().y + player1.getSpeed()});
			player1.update();
		}
		if (IsKeyDown(KEY_I)) {
			player2.setPosition({ player2.getPosition().x, player2.getPosition().y - player2.getSpeed()});
			player2.update();
		}
		if (IsKeyDown(KEY_K)) {
			player2.setPosition({ player2.getPosition().x, player2.getPosition().y + player2.getSpeed()});
			player2.update();
		}
		BeginDrawing();

		ClearBackground(BLACK);
		DrawText(TextFormat("%i", player1.getScore()), 100, 0, 32, WHITE);
		DrawText(TextFormat("%i", player2.getScore()), 700, 0, 32, WHITE);
		player1.draw();
		player2.draw();
		ball.draw();
		if (!start) {
			DrawText("Press Space to start", 300, 200, 32, WHITE);
		}
		//que se mueva la pelota al iniciar por unica vez
		if (IsKeyPressed(KEY_SPACE) && !start) {
			GetRandomValue(0, 1) == 0 ? ball.setSpeed({ -5, 0 }) : ball.setSpeed({ 5, 0 });
			start = true;
		}
		ball.setPosition({ ball.getPosition().x + ball.getSpeed().x, ball.getPosition().y + ball.getSpeed().y});
		//que se reinicie el juego
		if (IsKeyPressed(KEY_R)) {
			player1.setScore(0);
			player2.setScore(0);
			ball.setPosition({ 400, 225 });
		}

		if (ball.getPosition().x <= 0) {
			player2.setScore(player2.getScore() + 1);
			ball.setPosition({ 400, 225 });
			ball.setSpeed({ 5, 0 });
		}
		if (ball.getPosition().x >= 800) {
			player1.setScore(player1.getScore() + 1);
			ball.setPosition({ 400, 225 });
			ball.setSpeed({ -5, 0 });
		}

		//fisicas
		if (ball.getPosition().y <= 0 || ball.getPosition().y >= 450) {
			ball.setSpeed({ ball.getSpeed().x, -ball.getSpeed().y });
		}
		if (CheckCollisionCircleRec(ball.getPosition(), 10, { player1.getPosition().x, player1.getPosition().y, 20, 100 })) {
			if (player1.getPosition().y + 50 > ball.getPosition().y) {
								ball.setSpeed({ -ball.getSpeed().x, -3 });
			}
			else {
				ball.setSpeed({ -ball.getSpeed().x, 3 });
			}
		}
		if (CheckCollisionCircleRec(ball.getPosition(), 10, { player2.getPosition().x, player2.getPosition().y, 20, 100 })) {
			if (player2.getPosition().y + 50 > ball.getPosition().y) {
				ball.setSpeed({ -ball.getSpeed().x, -3 });
			}
			else {
				ball.setSpeed({ -ball.getSpeed().x, 3 });
			}
		}
		//limites para jugadores
		if (player1.getPosition().y <= 0) {
			player1.setPosition({ player1.getPosition().x, 0 });
		}
		if (player1.getPosition().y >= 350) {
			player1.setPosition({ player1.getPosition().x, 350 });
		}
		if (player2.getPosition().y <= 0) {
			player2.setPosition({ player2.getPosition().x, 0 });
		}
		if (player2.getPosition().y >= 350) {
			player2.setPosition({ player2.getPosition().x, 350 });
		}
		EndDrawing();
	}
	CloseWindow();
	return 0;
}