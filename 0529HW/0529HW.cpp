#include <iostream>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
using namespace std;

//1.요일 구하기
    //1년 1월 1일(월요일)을 기준으로 입력한 날짜까지 며칠이 지났는지 계산한 후, 7로 나눈 나머지로 요일을 구하기.
    //윤년도 올바르게 처리할 것
    //입력받은 연, 월, 일을 기준으로 요일을 출력.
        //예시 입력 : 2026 5 29 → 결과 : 금요일
            //Homework01_Run(); 함수로 실행 가능해야 함.

void Homework01_Run()
{
    while (1)
    {
        printf("연도, 월, 일을 입력하세요 (예: 2026 5 29)/(종료하려면 0 0 0 입력): ");
        int year, month, day;
        cin >> year >> month >> day;
        if (year != 0 && month != 0 && day != 0)
        {
            if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31)
            {
                printf("잘못된 입력입니다. 연도는 1 이상, 월은 1~12, 일은 1~31 사이여야 합니다.\n");
                return;
            }
            else
            {   // 1.윤년 계산
                bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
                int daysInMonth[] = { 31, isLeapYear ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

                //2.1년 1월 1일부터 입력한 날짜까지의 총 일수 계산
                int totalDays = (year - 1) * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400; // 윤년 포함
                for (int i = 0; i < month - 1; i++)
                {
                    totalDays += daysInMonth[i];
                }
                totalDays += day;
                //3.요일 계산
                string daysOfWeek[7] = { "월요일", "화요일", "수요일", "목요일", "금요일", "토요일", "일요일" };
                string dayOfWeek = daysOfWeek[totalDays % 7 - 1];
                cout << year << "년 " << month << "월 " << day << "일은 " << dayOfWeek << "입니다." << endl;
            }
        }
        else
        {
            printf("프로그램을 종료합니다.\n");
            break;
        }
    }
}





//2.블랙잭 만들기
    //1)게임 목표
        //두 카드의 합이 21에 가깝게 만들되, 21을 넘지 않는 것이 목표
        //21을 초과하면(버스트, Bust)  즉시 패배
        //배팅은 없음
    //2)카드의 값
        //2~10: 카드 숫자 그대로 점수.
        //J(잭), Q(퀸), K(킹) : 각각 10점.
        //A(에이스) : 1점 또는 11점(유리한 쪽으로 자동 선택).
    //3)게임 진행 절차
        //초기 배분
            //딜러와 플레이어 모두 2장씩 카드를 받음.
            //플레이어의 카드는 두 장 모두 공개.
            //딜러는 한 장은 공개(오픈 카드), 한 장은 비공개(홀 카드).
        //플레이어 턴
            //플레이어가 먼저 행동.
            //선택지:
                //Hit(히트) : 카드를 한 장 더 받음.
                //Stand(스탠드) : 더 이상 카드를 받지 않고 멈춤.
            //플레이어가 21을 초과하면(버스트) 즉시 패배.
        //딜러 턴
            //플레이어가 스탠드를 하면 딜러 차례.
            //딜러는 자신의 카드 합이 17 이상이 될 때까지 계속 히트(카드 받기)해야 함.
                //A가 포함된 "소프트 17"(A + 6 = 7 또는 17)도 멈춤.
            //17 이상이면 멈추고, 21을 넘으면 딜러 패배.
    //4)승패 판정
        //버스트가 아닌 경우, 점수 비교.
            //플레이어가 21에 더 가까우면 승리.
            //동점이면 무승부(Push).
            //딜러가 더 가까우면 패배.
        //블랙잭: 처음 받은 두 장이 A + 10(또는 J, Q, K)이면 블랙잭.일반적으로 블랙잭이 단순 21점보다 우선함.
    //Homework02_Run(); 함수로 실행 가능해야 함.

void ScoreCard(int &card, int &score, int &aceCount)
{
    int cardValue = card % 13;
    if (cardValue < 9)
    {
        score += cardValue+2; // 2~10
    }
    else if (cardValue < 12 && cardValue >= 9)
    {
        score += 10; // J, Q, K
    }
    else
    {
        score += 11; // A는 처음에 11점으로 계산
		aceCount++; // A의 변동 가능성 추적
    }
}


void AceAdjustment(int &score, int &aceCount)
{
    while (score > 21 && aceCount > 0)
    {
        score -= 10; // A를 11점에서 1점으로 조정
        aceCount--;
    }
}

void PrintCard(int cards)
{
    const char* Symbols[] = { "♠", "♥", "♣", "♦" };
    const char* values[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
    const char* Symbol = Symbols[cards / 13];
    const char* value = values[cards % 13];
    printf("%s%s ", Symbol, value);
}



void Homework02_Run()
{
    srand(time(0));
    int Deck[52];
    int randIdx = -1;
    for (int i = 0; i < 52; i++)
    {
        Deck[i] = i;
	}   //0~51까지의 숫자로 카드 덱 초기화 (0~12: ♠2~A, 13~25: ♥2~A, 26~38: ♣2~A, 39~51: ♦2~A)


    int playerCards[10] = { -1,-1, -1, -1, -1, -1, -1, -1, -1, -1 };    //최악의 경우 플레이어와 딜러가 각각 10장까지 받을 수 있다고 가정
	char playercardSymbols[10] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }; // 카드 심볼을 저장할 배열
	char playercardValues[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // 0~12로 카드 값(2~A)을 저장할 배열

    int dealerCards[10] = { -1,-1, -1, -1, -1, -1, -1, -1, -1, -1 };    //최악의 경우 플레이어와 딜러가 각각 10장까지 받을 수 있다고 가정
	int dealercardSymbols[10] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }; // 카드 심볼을 저장할 배열
	char dealercardValues[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // 0~12로 카드 값(2~A)을 저장할 배열


    int playerCardCount = 0, dealerCardCount = 0;
	int playerAceCount = 0, dealerAceCount = 0; // A의 개수를 추적하여 점수 계산에 활용


	int playerScore = 0, dealerScore = 0;

    // 초기 카드 배분

    //플레이어 카드 2개 배분
    randIdx = rand() % 52;
	playerCards[playerCardCount] = Deck[randIdx];   // 플레이어 첫 번째 카드 배분
	Deck[randIdx] = -1;  // 중복 방지 위해 덱에서 해당 카드 제거(-1)
	ScoreCard(playerCards[playerCardCount], playerScore, playerAceCount); // 플레이어 첫 번째 카드 점수 계산


	//출력할 카드 값과 심볼 저장
    
 //   if (playerCards[playerCardCount] % 13 < 9)
 //   {
 //       playercardValues[playerCardCount] = playerCards[playerCardCount] % 13 + 1; // 카드 값 저장 (2~10)
 //   }
 //   else if (playerCards[playerCardCount] % 13 ==10)
 //   {
 //       playercardValues[playerCardCount] = 'J'; // J
 //   }
 //   else if(playerCards[playerCardCount] % 13 == 11)
 //   {
 //       playercardValues[playerCardCount] = 'Q'; // Q
 //   }
 //   else if(playerCards[playerCardCount] % 13 == 12)
 //   {
 //       playercardValues[playerCardCount] = 'K'; // K
 //   }
 //   else
 //   {
 //       playercardValues[playerCardCount] = 'A'; // A
	//}

 //   if((playerCards[playerCardCount]+1)/13 == 0)
 //   {
 //       playercardSymbols[playerCardCount] = '♠'; // ♠
 //   }
 //   else if((playerCards[playerCardCount]+1)/13 == 1)
 //   {
 //       playercardSymbols[playerCardCount] = '♥'; // ♥
 //   }
 //   else if((playerCards[playerCardCount]+1)/13 == 2)
 //   {
 //       playercardSymbols[playerCardCount] = '♣'; // ♣
 //   }
 //   else if ((playerCards[playerCardCount] + 1) / 13 == 3)
 //   {
 //       playercardSymbols[playerCardCount] = '♦'; // ♦
 //   }

    playerCardCount++;




    while (playerCards[playerCardCount] == -1)
    {
        randIdx = rand() % 52;
		playerCards[playerCardCount] = Deck[randIdx];
	}// 플레이어 두 번째 카드 배분 (첫 번째 카드와 중복되지 않도록)

    playerCards[playerCardCount];
    Deck[randIdx] = -1;  // 중복 방지 위해 덱에서 해당 카드 제거(-1)
	ScoreCard(playerCards[playerCardCount], playerScore, playerAceCount); // 플레이어 두 번째 카드 점수 계산

	AceAdjustment(playerScore, playerAceCount); // A가 11점으로 계산된 경우, 점수가 21을 초과하면 A를 1점으로 변경
    playerCardCount++;

    // 플레이어 카드 공개

    printf("플레이어 카드: ");
    for (int i = 0; i < playerCardCount; i++)
    {
        PrintCard(playerCards[i]); // 플레이어 첫 번째 카드 심볼과 값 출력
    }

	//블랙잭 체크
    if(playerScore == 21)
    {
        printf("\n블랙잭! 플레이어 승리!\n");
        return;
	}

    printf("\n플레이어 점수: %d\n", playerScore);
    if (playerScore > 21)
    {
        printf("버스트! 플레이어 패배.\n");
        return;
    }




    printf("=================================\n");




	//딜러 카드 2개 배분
    while (dealerCards[dealerCardCount] == -1)
    {
        randIdx = rand() % 52;
		dealerCards[dealerCardCount] = Deck[randIdx];
	}   // 딜러 첫 번째 카드 배분 (플레이어 카드와 중복되지 않도록)

	Deck[randIdx] = -1;  // 중복 방지 위해 덱에서 해당 카드 제거(-1)
	ScoreCard(dealerCards[dealerCardCount], dealerScore, dealerAceCount); // 딜러 첫 번째 카드 점수 계산
    dealerCardCount++;



	while (dealerCards[dealerCardCount] == -1)
    {
        randIdx = rand() % 52;
		dealerCards[dealerCardCount] = Deck[randIdx];
    }
    Deck[randIdx] = -1;  // 중복 방지 위해 덱에서 해당 카드 제거(-1)
    ScoreCard(dealerCards[dealerCardCount], dealerScore, dealerAceCount); // 딜러 두 번째 카드 점수 계산
    
    AceAdjustment(dealerScore, dealerAceCount); // A가 11점으로 계산된 경우, 점수가 21을 초과하면 A를 1점으로 변경
    dealerCardCount++;

	// 딜러 카드 공개 (첫 번째 카드만 공개)
    printf("\n딜러 카드: ");
    PrintCard(dealerCards[0]); // 딜러 첫 번째 카드 심볼과 값 출력
    printf(" ?\n");




    printf("=================================\n");




    // 플레이어 턴
    char playerChoice;
    while (true)
    {
        printf("Hit(H) 또는 Stand(S)를 선택하세요: ");
        cin >> playerChoice;
        if (playerChoice == 'H' || playerChoice == 'h')
        {
            // 플레이어 히트
            while (playerCards[playerCardCount] == -1)
            {
                randIdx = rand() % 52;
				playerCards[playerCardCount] = Deck[randIdx];
			}   // 플레이어 추가 카드 배분 (중복 방지)

            Deck[randIdx] = -1;  // 중복 방지 위해 덱에서 해당 카드 제거(-1)
            ScoreCard(playerCards[playerCardCount], playerScore, playerAceCount); // 플레이어 추가 카드 점수 계산

            AceAdjustment(playerScore, playerAceCount); // A가 11점으로 계산된 경우, 점수가 21을 초과하면 A를 1점으로 변경
            playerCardCount++;
            // 플레이어 카드 공개
            printf("플레이어 카드: ");
            for (int i = 0; i < playerCardCount; i++)
            {
				PrintCard(playerCards[i]);
            }

            printf("\n플레이어 점수: %d\n", playerScore);
            if (playerScore > 21)
            {
                printf("버스트! 플레이어 패배.\n");
                return;
            }
        }
        else if (playerChoice == 'S' || playerChoice == 's')
        {
            // 플레이어 스탠드
            break;
        }
        else
        {
            printf("잘못된 입력입니다. Hit(H) 또는 Stand(S)를 선택하세요.\n");
		}
	}





    printf("=================================\n");




    // 딜러 턴
    printf("\n딜러 카드: ");
    for (int i = 0; i < dealerCardCount; i++)
    {
        PrintCard(dealerCards[i]);
    }
    printf("\n딜러 점수: %d\n", dealerScore);


    while (dealerScore < 17 || (dealerScore == 17 && dealerAceCount > 0)) // 딜러가 17 미만이거나 소프트 17인 경우 계속 히트
    {
        while (dealerCards[dealerCardCount] == -1)
        {
            randIdx = rand() % 52;
            dealerCards[dealerCardCount] = Deck[randIdx];
        }   // 딜러 추가 카드 배분 (중복 방지)

        Deck[randIdx] = -1;  // 중복 방지 위해 덱에서 해당 카드 제거(-1)
        ScoreCard(dealerCards[dealerCardCount], dealerScore, dealerAceCount); // 딜러 추가 카드 점수 계산

        AceAdjustment(dealerScore, dealerAceCount); // A가 11점으로 계산된 경우, 점수가 21을 초과하면 A를 1점으로 변경
        dealerCardCount++;

        // 딜러 카드 공개
        printf("\n딜러 카드: ");
        for (int i = 0; i < dealerCardCount; i++)
        {
			PrintCard(dealerCards[i]);
        }
        printf("\n딜러 점수: %d\n", dealerScore);
    }
    // 승패 판정
    if (dealerScore > 21)
    {
        printf("딜러 버스트! 플레이어 승리.\n");
    }
    else if (playerScore > dealerScore)
    {
        printf("플레이어 승리!\n");
    }
    else if (playerScore < dealerScore)
    {
        printf("딜러 승리!\n");
    }
    else
    {
        printf("무승부! Push.\n");
	}


}




int main()
{
    //Homework01_Run();
    Homework02_Run();
	return 0;

}
