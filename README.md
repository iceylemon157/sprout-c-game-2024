# 資訊之芽 2024 大作業二

## How to Start

### 遊戲畫面

用以下指令可以把 遊戲 (client) 跟 C++ server 架起來

```bash
git clone https://github.com/iceylemon157/sprout-c-game-2024
cd sprout-c-game-2024
docker compose up
```

此時在瀏覽器中打開 `localhost:12345/app` 即可看到遊戲畫面。

### C++ server

接著開一個新的 terminal，先 `cd` 到 `cd sprout-c-game-2024` 裡面，然後執行以下指令就可以把 C++ server 跑起來

```bash
docker compose exec cpp_server /bin/bash
(在 docker 裡面) make && ./server
```

