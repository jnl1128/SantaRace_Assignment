#include <bangtal.h>
using namespace bangtal;

int main()
{
	//0. 배경 옵션 변경
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);//기본적으로 보였던 우측 상단의 인벤토리 박스가 안보이게 됨.

	//1. 배경, 배경 역할 오브젝트 생성
	auto scene1 = Scene::create("철수 방", "images/room.jpg");
	auto windowX = 1000;
	auto windowY = 400;
	auto window = Object::create("images/window.png", scene1, windowX, windowY);
	window->setScale(0.5f);
	auto bedX = 500;
	auto bed = Object::create("images/bed.png", scene1, bedX, -50);
	bed->setScale(1.2f);
	auto tableX = 1300;
	auto table = Object::create("images/table.png", scene1, tableX, -20);
	table->setScale(0.5f);
	auto cabinet_open = false;
	auto cabinetX = -200;
	auto cabinet = Object::create("images/closed_cabinet.png", scene1, cabinetX, 60);
	cabinet->setScale(0.25f);
	auto closet_open = false;
	auto closetX = -20;
	auto closet = Object::create("images/closed_closet.png", scene1, closetX, 60);
	closet->setScale(0.85f);

	//3. 오브젝트 생성
	auto bag_pick = false;
	auto bagX = 800;
	auto bag = Object::create("images/bag.png", scene1, bagX, 140);
	bag->setScale(0.25f);
	auto books_pick = false;
	auto booksX = 600;
	auto books = Object::create("images/books.png", scene1, booksX, 50);
	books->setScale(0.15f);
	auto apple_pick = false;
	auto appleX = 1400;
	auto apple = Object::create("images/apple.png", scene1, appleX, 200);
	apple->setScale(0.13f);
	auto cap_pick = false;
	auto capX = 150;
	auto cap = Object::create("images/cap.png", scene1, capX, 100,false);
	cap->setScale(0.2f);
	auto boy = Object::create("images/boy.png", scene1, 0, 0);
	boy->setScale(0.5f);
	showMessage("헉! 코딩하다보니 벌써 아침이네!!\n 10초 내로 준비하지 않으면 난 지각이야!!\n나 대신 가방에 책, 사과, 그리고 모자 좀 넣어줘!");

	//3-1. 오브젝트 이벤트 생성
	bag->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool
		{
			bag->hide();
			bag_pick = true;
			return true;
		});
	books->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool
		{
			books->hide();
			books_pick = true;
			return true;
		});
	apple->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool
		{
			apple->hide();
			apple_pick = true;
			return true;
		});
	cap->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool
		{
			cap->hide();
			cap_pick = true;
			return true;
		});
	cabinet->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool
		{
			if (!cabinet_open)
			{
				cabinet->setImage("images/opened_cabinet.png");
				cabinet_open = true;
			}
			else
			{
				cabinet->setImage("images/closed_cabinet.png");
				cabinet_open = false;
				
			}
			return true;
		});
	closet->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool
		{
			if (!closet_open)
			{
				closet->setImage("images/opened_closet.png");
				closet_open = true;
				cap->hide();//pick된 상태에서의 cap
				if (!cap_pick)
				{
					cap->show();//옷장 문 열면 cap 보이게(pick안된 상태에서의 cap)
				}
			}
			else
			{
				closet->setImage("images/closed_closet.png");
				closet_open = false;
				cap->hide(); //옷장 문 닫으면 cap 안 보이게
			}
			return true;
		});

	//4. 타이머 생성
	auto timer = Timer::create(10.f);
	showTimer(timer);

	//5. 버튼 생성
	auto startButton = Object::create("images/start.png", scene1, 580, 10); //게임 시작 버튼
	startButton->setScale(0.1f);
	auto stopButton = Object::create("images/stop.png", scene1, 680, 10); //게임 종료 버튼
	stopButton->setScale(0.1f);
	auto restartButton = Object::create("images/restart.png", scene1, 580, 10,false);//게임 재시작 버튼
	restartButton->setScale(0.1f);
	auto leftButton = Object::create("images/left.png", scene1, 520, 670);//왼쪽으로 30만큼 이동 버튼
	leftButton->setScale(0.1f);
	auto rightButton = Object::create("images/right.png", scene1, 700, 670);//오른쪽으로 30만큼 이동 버튼
	rightButton->setScale(0.1f);
	auto schoolButton = Object::create("images/school.png", scene1, 0, 650);//게임 미션 완료했음을 알리는 버튼
	schoolButton->setScale(0.2f);

	//5-1. 버튼 이벤트 생성
	leftButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action) -> bool
			{
				//5-1-1. 화면 x축으로 30만큼 이동
			if (windowX < 1200)
			{
				windowX = windowX + 30;
				window->locate(scene1, windowX, windowY);
				bedX = bedX + 30;
				bed->locate(scene1, bedX, -50);
				tableX = tableX + 30;
				table->locate(scene1, tableX, -20);
				bagX = bagX + 30;
				bag->locate(scene1, bagX, 140);
				booksX = booksX + 30;
				books->locate(scene1, booksX, 50);
				appleX = appleX + 30;
				apple->locate(scene1, appleX, 200);
				cabinetX = cabinetX + 30;
				cabinet->locate(scene1, cabinetX, 60);
				capX = capX + 30;
				cap->locate(scene1, capX, 100);
				closetX = closetX + 30;
				closet->locate(scene1, closetX, 60);
			}
			else {
				showMessage("여긴 더이상 없어!");//좌우로 갈 수 있는 범위 제한
			}
				return true;
			});
	rightButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action) -> bool
		{

			if (windowX > 600)
			{
				windowX = windowX - 30;
				window->locate(scene1, windowX, windowY);
				bedX = bedX - 30;
				bed->locate(scene1, bedX, -50);
				tableX = tableX - 30;
				table->locate(scene1, tableX, -20);
				bagX = bagX - 30;
				bag->locate(scene1, bagX, 140);
				booksX = booksX - 30;
				books->locate(scene1, booksX, 50);
				appleX = appleX - 30;
				apple->locate(scene1, appleX, 200);
				cabinetX = cabinetX - 30;
				cabinet->locate(scene1, cabinetX, 60);
				capX = capX - 30;
				cap->locate(scene1, capX, 100);
				closetX = closetX - 30;
				closet->locate(scene1, closetX, 60);
			}
			else
			{
				showMessage("여긴 더이상 없어!"); //좌우로 갈 수 있는 범위 제한
			}
			return true;
		});
	stopButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action) -> bool
		{
			endGame();
			return true;
		});
	startButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action) -> bool
		{
			boy->setImage("images/boy.png");
			boy->hide();
			startButton->hide();
			stopButton->hide();
			leftButton->show();
			rightButton->show();
			timer->set(10.f); // 재시작할때 타이머 10초로 재설정
			timer->start();

			//새로운 게임 시작할때 배경 및 오브젝트 첫 시작 위치로 재설정
			windowX = 1000; // 
			window->locate(scene1, windowX, windowY);
			bedX = 500;
			bed->locate(scene1, bedX, -50);
			tableX = 1300;
			table->locate(scene1, tableX, -20);
			bagX = 800;
			bag->locate(scene1, bagX, 140);
			booksX = 600;
			books->locate(scene1, booksX, 50);
			appleX = 1500;
			apple->locate(scene1, appleX, 200);
			cabinetX = -200;
			cabinet->locate(scene1, cabinetX, 60);
			capX = 150;
			cap->locate(scene1, capX, 100);
			closetX = -20;
			closet->locate(scene1, closetX, 60);
			return true;
		});

	restartButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action) -> bool
		{
			boy->setImage("images/boy.png");
			boy->show();
			//새로운 게임 시작할 때 오브젝트 다시 생성
			cap->hide();
			cap_pick = false;
			closet->setImage("images/closed_closet.png");
			apple->show();
			apple_pick = false;
			bag->show();
			bag_pick = false;
			books->show();
			books_pick = false;
			restartButton->hide();
			startButton->show();
			stopButton->show();
			showMessage("헉! 코딩하다보니 벌써 아침이네!!\n 10초 내로 준비하지 않으면 난 지각이야!!\n나 대신 가방에 책, 사과, 그리고 모자 좀 넣어줘!");
			return true;
		});
	timer->setOnTimerCallback([&](TimerPtr) -> bool
		{
			//게임 미션 실패시
			boy->setImage("images/sad.png");
			boy->show();
			showMessage("지각이다ㅜㅜ");
			restartButton->show();
			stopButton->show();
			return true;
		});
	schoolButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action) -> bool
		{
			if (bag_pick && books_pick && apple_pick && cap_pick)
			{
				//게임 미션 성공시
				boy->setImage("images/smile.png");
				boy->show();
				showMessage("덕분에 지각하지 않을 수 있었어! 고마워~");
				timer->stop();
				restartButton->show();
				stopButton->show();
				leftButton->hide();
				rightButton->hide();
			}
			else
			{
				//시간은 넘지 않았지만 미션 완료 조건을 채우지 않고 완료 버튼을 눌렀을 때
				showMessage("아직 학교 갈 준비가 안됐어ㅜㅜ");
			}
			return true;
		});

	//2. 게임 시작 
	startGame(scene1);

	return 0;
}