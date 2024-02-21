遊戲名稱：battle-city
打開方式：pull檔案後用 Qt creator 打開
遊戲玩法:
1.進入遊戲之後可以選擇單/雙人遊戲模式，以及關卡。單人模式透過上下左右空白鍵控制角色的移動和發射子彈，雙人模式下的另一角色則以wasd和shift健控制。
2.遊戲過程要避免被敵人子彈擊中，當玩家生命值歸零亦或老鷹被擊中時遊戲失敗，當玩家成功消滅20個敵人時遊戲勝利。
程式邏輯:
透過Qwidget對QgraphicsScene的show和close做遊戲頁面的轉換，並在scene內做遊戲的創建。
設計不同的function，當有碰撞或keypressevent等事件發生時，便會呼叫不同的function去執行。
可以透過額外file(.txt)的讀出和寫入紀錄遊戲進度
