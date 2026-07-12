# IVS

HL만도·HL클레무브 IVS 교육에서 진행한 실습과 프로젝트 코드를 정리한 저장소입니다.

## 프로젝트

### [CANoe CAPL 블랙박스 테스트](./BLACK_BOX_TESTING_WITH_CANOE)

ECU의 FailSafe 요구사항이 경계값과 시간 조건에 맞게 동작하는지 검증하는 블랙박스 테스트 프로젝트입니다. 요구사항을 동등 분할과 경계값 분석으로 테스트 케이스화하고, CANoe/CAPL로 입력 신호 주입과 응답 판정을 자동화했습니다.

저장소에는 다음 자료가 포함되어 있습니다.

- CANoe 수동 테스트 패널 및 ECU별 CAPL 코드
- Battery, Ignition, Engine, Brake, Steering 관련 자동 테스트 스크립트
- 테스트 케이스 문서

`CANoe` `CAPL` `CAN` `Black-box Testing` `EP/BVA`

### [STM32 기초 실습](./STM-32)

STM32L0 Nucleo 보드에서 GPIO 제어 방식을 단계별로 확인한 기초 실습입니다. 레지스터 직접 제어, HAL Driver, BSP 방식의 GPIO 예제와 버튼 및 진동 감지 센서를 이용한 인터럽트 코드를 포함합니다.

`C` `STM32L0` `GPIO` `HAL` `BSP` `Interrupt`
