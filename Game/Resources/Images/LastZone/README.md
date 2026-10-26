# LAST ZONE 이미지 리소스 v1

## 2주차 연결 업데이트

현재 게임 코드에서 배경·캐릭터·조준점과 시작 효과음을 사용한다. 전투 효과 이미지 및 나머지 효과음은 후속 전투 구현용으로 준비했다. 아래 내용은 초기 생성 기록이며, 실제 캐릭터 출력은 ResourceManager.cpp의 행별 보정 영역을 사용한다. 원본 행 경계로 자르면 다음 행의 일부가 포함될 수 있다.

내장 이미지 생성 도구(image_gen)로 제작한 초기 게임 리소스. 기존 파일을 교체하지 않고 새로 추가했다.

## 파일

| 파일 | 실제 크기 | 내용 |
|---|---|---|
| characters_walk_v1.png | 1254 × 1254, RGBA | 플레이어와 좀비 3종의 오른쪽 방향 걷기 시트 |
| arena_v1.png | 1672 × 941, RGB | 고정 전투 경기장 배경 |

캐릭터 시트의 실제 알파 채널 범위는 0~255로, 투명 배경을 포함한다. 배경은 게임 화면 전체에 맞춰 그린다. 1280×720과 비율이 거의 같지만 정확히 일치하지 않으므로 출력 영역에 맞춰 크기를 설정한다.

## 캐릭터 시트 사용

4열 × 4행 구성. 위에서부터 플레이어, 일반 좀비, 빠른 좀비, 튼튼한 좀비이며, 왼쪽부터 걷기 프레임 0~3이다. 모든 캐릭터는 오른쪽을 향한다.

생성 결과가 요청한 1024×1024와 달리 1254×1254이므로 고정 256픽셀로 자르면 안 된다. 픽셀 경계 배열 [0, 314, 627, 941, 1254]를 가로·세로에 공통으로 사용한다. 셀 (열 c, 행 r)의 영역은 x=경계[c], y=경계[r], 폭=경계[c+1]-경계[c], 높이=경계[r+1]-경계[r]이다. 우측·하단 좌표는 포함하지 않는 기준이다.

초기 재생 속도는 초당 6~8프레임을 권장한다. 왼쪽 이동은 좌우 반전으로 표현할 수 있다. 위·아래 전용 방향, 대기·피격·사망 전용 시트는 이번 묶음에 포함되어 있지 않다. 총구 섬광·총알·UI·사운드도 아직 포함되지 않았다.

## 적용 시 확인 사항

- 생성 이미지이므로 각 프레임의 발 위치와 실루엣이 완벽하게 일치하지 않는다. 실제 게임에서 중심점과 표시 크기를 조정하며 걷기 흔들림을 확인한다.
- 시트의 셀 크기와 화면상의 캐릭터 크기는 별개다. 플레이어 표시 높이를 약 60~80픽셀부터 시험한다.
- 그림은 3/4 시점이며 배경은 위에서 본 경기장이다. 실제 합성 화면에서 시점과 크기의 조화를 확인한다.
- 배경 가장자리의 차·울타리는 이미지 장식이다. 별도 충돌 영역을 만들기 전에는 플레이어 이동을 안쪽 사각형으로 제한한다.
- 현재 C++ 소스에는 이미지 로딩이나 애니메이션 처리를 연결하지 않았다.

## 제작 기록

제작일: 2026-10-26. 제작 방식: 내장 image_gen. 아래는 실제 사용한 프롬프트다.

### 캐릭터 시트

Use case: stylized-concept. Asset type: transparent PNG sprite atlas for LAST ZONE, a C++ 2D top-down zombie shooter. Create a clean pixel art sprite sheet, exactly 4 columns by 4 rows, 1024x1024 canvas, equal 256x256 cells, transparent background. Each row is one consistent character, each column a four-frame walking cycle facing screen right, same centered feet pivot and scale across frames. Row 1: human survivor in blue jacket holding small pistol pointed right. Row 2: ordinary slim green zombie in torn brown clothing reaching right. Row 3: fast skinny pale zombie in torn red clothing leaning forward. Row 4: heavy broad purple-gray zombie in torn dark workwear. Top-down three-quarter arcade pixel art perspective, visible heads shoulders bodies feet, crisp hard pixel edges, dark outlines, limited readable palette. Each sprite fits within central 160x180 area of its cell with generous transparent gutters. Four distinct alternating leg and arm poses, identical character identity across row. No labels, grid lines, floor, shadows outside character, scenery, text, watermark or interface. Actual alpha transparency.

### 경기장 배경

Use case: stylized-concept. Asset type: game arena background for LAST ZONE, 2D top-down zombie shooter. Landscape 16:9 image. Crisp detailed pixel art, muted charcoal asphalt, cool blue gray concrete, restrained rusty orange accents, abandoned urban quarantine yard at dusk. Orthographic overhead view, no horizon, no perspective vanishing point. Entire central 80 percent is open flat walkable asphalt with subtle cracks and faded road marks, low contrast so characters and bullets remain readable. Only the outer border contains abandoned car wrecks, chain-link fence segments, concrete barriers, few barrels, subtle lamps and rubble. Keep openings at middle of each edge for enemy spawning. No tall objects or obstacles in central playable area. No characters, zombies, weapons, corpses, text, signs with writing, HUD, logos or watermark. Flat even readable lighting, no heavy fog. Finished standalone background texture, not a screenshot or mockup.

