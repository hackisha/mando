# IVS

HL만도·HL클레무브 IVS 교육에서 진행한 차량 제어기 검증과 STM32 GPIO 실습 자료입니다.

- Vector CANoe/CAPL 기반 ECU 블랙박스 테스트
- 동등 분할과 경계값 분석을 이용한 테스트 케이스 설계
- 시스템 변수 기반 ECU 입력 주입과 Fault Level 판정
- STM32L0 Nucleo 기반 GPIO 직접 제어, HAL, BSP 실습
- Polling과 EXTI interrupt를 이용한 버튼·진동 센서 처리

## 저장소 구성

```text
IVS/
├── BLACK_BOX_TESTING_WITH_CANOE/
│   ├── IVS_TestCase.xlsx
│   ├── manualTest/
│   └── testScript(capl)/
└── STM-32/
    ├── GPIO/
    ├── GPIO_HAL/
    ├── GPIO_BSP/
    └── BSP/
        ├── Polling/
        └── Interrupt/
```

## CANoe CAPL 블랙박스 테스트

ECU의 FailSafe 요구사항이 경계값과 시간 조건에 맞게 동작하는지 검증하는 프로젝트입니다. CANoe 시스템 변수로 입력을 주입하고 `Fault_sts_Rsp` 응답을 받아 기대 Fault Level과 비교합니다.

### 테스트 흐름

```text
사전조건 및 시스템 변수 설정
  -> ECU 모의 노드 주기 메시지 활성화
  -> 고장 상태 초기화 또는 조회
  -> 정상값·고장값·경계값 주입
  -> 검출 또는 회복 시간 대기
  -> Fault_sts_Rsp 수신
  -> expected level과 actual level 비교
  -> testStepPass / testStepFail
```

Fault Level은 다음 값으로 판정합니다.

| Level | 의미 |
| ---: | --- |
| `0` | 고장 없음 |
| `1` | 고장 회복 후 저장 상태 |
| `2` | 고장 검출 상태 |

### 수동 입력 노드

| 파일 | 입력 신호 | 송신 주기 |
| --- | --- | ---: |
| `ECU_BMS.can` | 충전 상태, 배터리 잔량·전압 | 10 ms |
| `ECU_BRK.can` | 가속 페달, 브레이크, 차량 속도 | 10 ms |
| `ECU_STR.can` | 조향각 | 10 ms |
| `ECU_UDS.can` | 고장 상태 조회·초기화 요청 | 10 ms |

### 자동 테스트 대상

| CAPL 파일 | 검증 대상 |
| --- | --- |
| `BatteryPercentLow.can` | 저전압 배터리 잔량 고장 |
| `BatteryChargeErr.can` | 배터리 충전 상태 고장 |
| `BatteryHighVoltage` | 배터리 과전압 고장 |
| `IgnitionStatusErr.can` | Ignition 상태 고장 |
| `EngineStatusErr.can` | Engine 상태 고장 |
| `BrakeErr.can` | Brake, Accelerator, Vehicle Speed 입력 고장 |
| `SteeringErr.can` | 조향각 범위 고장 |

테스트는 검출 사전조건, 동등 분할, 임계값 전후, 검출·회복 시간, 재검출과 Ignition cycle 조건을 포함합니다. 정확한 입력값과 기대 결과는 [`IVS_TestCase.xlsx`](./BLACK_BOX_TESTING_WITH_CANOE/IVS_TestCase.xlsx)와 각 CAPL 파일을 기준으로 확인해야 합니다.

### 실행 환경

다음 항목은 저장소에 포함되어 있지 않습니다.

- CANoe configuration
- DBC와 시스템 변수 정의
- 시험 대상 ECU 실행 파일 또는 모델
- CANoe Test Module 설정

CAPL 스크립트를 실행하려면 메시지와 시스템 변수 이름이 일치하는 별도 CANoe 환경이 필요합니다.

## STM32 GPIO·인터럽트 실습

STM32L0 Nucleo 보드에서 GPIO를 제어하는 방식을 레지스터 직접 접근부터 HAL, BSP 순서로 확인한 기초 실습입니다.

| 경로 | 내용 |
| --- | --- |
| `GPIO/` | 레지스터 주소와 bit mask를 이용한 GPIO 직접 제어 |
| `GPIO_HAL/` | `HAL_GPIO_*` API 기반 LED 제어 |
| `GPIO_BSP/` | `BSP_LED_*` API 기반 LED 제어 |
| `BSP/Polling/` | User Button polling과 LED 제어 |
| `BSP/Interrupt/` | EXTI callback 기반 LED toggle |
| `BSP/Interrupt/SW-420/` | SW-420 진동 센서 interrupt 처리 |

레지스터 예제는 GPIO clock을 활성화하고 PA5, PA8, PB5를 출력으로 설정합니다. 인터럽트 예제는 `HAL_GPIO_EXTI_Callback()`에서 입력 핀을 확인해 LED 상태를 변경합니다.

### 빌드 환경

실행에는 대상 보드에 맞는 다음 환경이 필요합니다.

- STM32CubeIDE 또는 ARM 호환 toolchain
- STM32L0 HAL과 CMSIS
- startup file과 linker script
- Nucleo 보드 및 SW-420 배선

모든 폴더에 완전한 STM32CubeIDE 프로젝트와 공통 빌드 스크립트가 포함된 것은 아닙니다.

## 제한사항

- CANoe 전용 구성과 ECU가 없어 저장소만으로 자동 테스트를 재현할 수 없습니다.
- STM32 예제는 보드, HAL/CMSIS와 프로젝트 설정을 별도로 준비해야 할 수 있습니다.
- 저장소에는 자동화된 빌드·테스트와 별도 라이선스 파일이 없습니다.
