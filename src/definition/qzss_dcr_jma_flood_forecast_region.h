#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_flood_forecast_region
// Variable      : qzss_dcr_jma_flood_forecast_region
// Entries       : 392
// Strategy      : binary_search

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

#if (AZARAC_ENABLE_FLOOD)

struct QZSS_DCR_JMA_FLOOD_FORECAST_REGION_Entry { uint64_t id; std::string_view label; };
inline constexpr QZSS_DCR_JMA_FLOOD_FORECAST_REGION_Entry QZSS_DCR_JMA_FLOOD_FORECAST_REGION_TABLE[] = {
    {10175000100u, std::string_view{"新川(北海道道央)", 23}},

    {19999999999u, std::string_view{"北海道のその他の河川", 30}},

    {20036000100u, std::string_view{"堤川・駒込川(青森県)", 29}},

    {29999999999u, std::string_view{"青森県のその他の河川", 30}},

    {39999999999u, std::string_view{"岩手県のその他の河川", 30}},

    {40028000100u, std::string_view{"七北田川(宮城県)", 23}},

    {49999999999u, std::string_view{"宮城県のその他の河川", 30}},

    {59999999999u, std::string_view{"秋田県のその他の河川", 30}},

    {60016000100u, std::string_view{"日向川(山形県)", 20}},

    {69999999999u, std::string_view{"山形県のその他の河川", 30}},

    {70006000100u, std::string_view{"宇多川(福島県)", 20}},

    {70010000100u, std::string_view{"新田川(福島県)", 20}},

    {70028000100u, std::string_view{"夏井川(福島県)", 20}},

    {79999999999u, std::string_view{"福島県のその他の河川", 30}},

    {89999999999u, std::string_view{"茨城県のその他の河川", 30}},

    {99999999999u, std::string_view{"栃木県のその他の河川", 30}},

    {109999999999u, std::string_view{"群馬県のその他の河川", 30}},

    {119999999999u, std::string_view{"埼玉県のその他の河川", 30}},

    {129999999999u, std::string_view{"千葉県のその他の河川", 30}},

    {130005000100u, std::string_view{"目黒川(東京都)", 20}},

    {130006000100u, std::string_view{"渋谷川・古川(東京都)", 29}},

    {139999999999u, std::string_view{"東京都のその他の河川", 30}},

    {140019000100u, std::string_view{"酒匂川(神奈川県)", 23}},

    {149999999999u, std::string_view{"神奈川県のその他の河川", 33}},

    {159999999999u, std::string_view{"新潟県のその他の河川", 30}},

    {169999999999u, std::string_view{"富山県のその他の河川", 30}},

    {179999999999u, std::string_view{"石川県のその他の河川", 30}},

    {180006000100u, std::string_view{"南川(福井県)", 17}},

    {180014000100u, std::string_view{"笙の川(福井県)", 20}},

    {189999999999u, std::string_view{"福井県のその他の河川", 30}},

    {199999999999u, std::string_view{"山梨県のその他の河川", 30}},

    {209999999999u, std::string_view{"長野県のその他の河川", 30}},

    {219999999999u, std::string_view{"岐阜県のその他の河川", 30}},

    {220062000100u, std::string_view{"瀬戸川・朝比奈川(静岡県)", 35}},

    {220079000100u, std::string_view{"太田川・原野谷川(静岡県)", 35}},

    {220081000100u, std::string_view{"都田川(静岡県)", 20}},

    {229999999999u, std::string_view{"静岡県のその他の河川", 30}},

    {230029000100u, std::string_view{"境川・逢妻川(愛知県)", 29}},

    {230052000100u, std::string_view{"天白川(愛知県)", 20}},

    {230054000100u, std::string_view{"日光川(愛知県)", 20}},

    {239999999999u, std::string_view{"愛知県のその他の河川", 30}},

    {249999999999u, std::string_view{"三重県のその他の河川", 30}},

    {259999999999u, std::string_view{"滋賀県のその他の河川", 30}},

    {269999999999u, std::string_view{"京都府のその他の河川", 30}},

    {270013000100u, std::string_view{"大津川・槇尾川(大阪府)", 32}},

    {270013000200u, std::string_view{"牛滝川(大阪府)", 20}},

    {279999999999u, std::string_view{"大阪府のその他の河川", 30}},

    {280014000100u, std::string_view{"武庫川(兵庫県)", 20}},

    {280053000100u, std::string_view{"市川(兵庫県)", 17}},

    {280064000100u, std::string_view{"千種川(兵庫県)", 20}},

    {289999999999u, std::string_view{"兵庫県のその他の河川", 30}},

    {299999999999u, std::string_view{"奈良県のその他の河川", 30}},

    {300013000100u, std::string_view{"古座川(和歌山県)", 23}},

    {300066000100u, std::string_view{"日高川(和歌山県)", 23}},

    {300077000100u, std::string_view{"有田川(和歌山県)", 23}},

    {309999999999u, std::string_view{"和歌山県のその他の河川", 33}},

    {310027000100u, std::string_view{"由良川(鳥取県)", 20}},

    {319999999999u, std::string_view{"鳥取県のその他の河川", 30}},

    {320004000100u, std::string_view{"益田川(島根県)", 20}},

    {320011000100u, std::string_view{"周布川(島根県)", 20}},

    {329999999999u, std::string_view{"島根県のその他の河川", 30}},

    {330009000100u, std::string_view{"笹ヶ瀬川・足守川(岡山県)", 35}},

    {339999999999u, std::string_view{"岡山県のその他の河川", 30}},

    {340013000100u, std::string_view{"沼田川(広島県)", 20}},

    {340021000100u, std::string_view{"黒瀬川(広島県)", 20}},

    {349999999999u, std::string_view{"広島県のその他の河川", 30}},

    {350002000102u, std::string_view{"錦川下流部(山口県)", 26}},

    {350002000103u, std::string_view{"錦川中流部(山口県)", 26}},

    {350019000100u, std::string_view{"島田川(山口県)", 20}},

    {350036000100u, std::string_view{"椹野川(山口県)", 20}},

    {350036001900u, std::string_view{"仁保川(山口県)", 20}},

    {350046000100u, std::string_view{"厚東川(山口県)", 20}},

    {359999999999u, std::string_view{"山口県のその他の河川", 30}},

    {360007000100u, std::string_view{"勝浦川(徳島県)", 20}},

    {369999999999u, std::string_view{"徳島県のその他の河川", 30}},

    {370026000100u, std::string_view{"香東川(香川県)", 20}},

    {379999999999u, std::string_view{"香川県のその他の河川", 30}},

    {389999999999u, std::string_view{"愛媛県のその他の河川", 30}},

    {399999999999u, std::string_view{"高知県のその他の河川", 30}},

    {400018000100u, std::string_view{"御笠川(福岡県)", 20}},

    {409999999999u, std::string_view{"福岡県のその他の河川", 30}},

    {419999999999u, std::string_view{"佐賀県のその他の河川", 30}},

    {429999999999u, std::string_view{"長崎県のその他の河川", 30}},

    {439999999999u, std::string_view{"熊本県のその他の河川", 30}},

    {440008000100u, std::string_view{"駅館川(大分県)", 20}},

    {449999999999u, std::string_view{"大分県のその他の河川", 30}},

    {450026000100u, std::string_view{"清武川(宮崎県)", 20}},

    {450040000100u, std::string_view{"広渡川(宮崎県)", 20}},

    {450040000700u, std::string_view{"酒谷川(宮崎県)", 20}},

    {459999999999u, std::string_view{"宮崎県のその他の河川", 30}},

    {460060000100u, std::string_view{"万之瀬川・加世田川(鹿児島県)", 41}},

    {469999999999u, std::string_view{"鹿児島県のその他の河川", 33}},

    {479999999999u, std::string_view{"沖縄県のその他の河川", 30}},

    {809999999999u, std::string_view{"沖縄県のその他の河川", 30}},

    {810101000100u, std::string_view{"天塩川(北海道道北)", 26}},

    {810101008500u, std::string_view{"名寄川(北海道道北)", 26}},

    {810102000100u, std::string_view{"留萌川(北海道道北)", 26}},

    {810103000101u, std::string_view{"石狩川上流(北海道道北)", 32}},

    {810103000102u, std::string_view{"石狩川下流(北海道道央)", 32}},

    {810103003100u, std::string_view{"豊平川(北海道道央)", 26}},

    {810103003101u, std::string_view{"石狩川水系豊平川上流(北海道道央)", 47}},

    {810103008100u, std::string_view{"千歳川(北海道道央)", 26}},

    {810103011900u, std::string_view{"夕張川(北海道道央)", 26}},

    {810103018200u, std::string_view{"幾春別川(北海道道央)", 29}},

    {810103025001u, std::string_view{"空知川上流(北海道道北)", 32}},

    {810103025002u, std::string_view{"空知川下流(北海道道央)", 32}},

    {810103033400u, std::string_view{"雨竜川(北海道道央)", 26}},

    {810103040900u, std::string_view{"忠別川(北海道道北)", 26}},

    {810103041000u, std::string_view{"美瑛川(北海道道北)", 26}},

    {810103044200u, std::string_view{"牛朱別川(北海道道北)", 29}},

    {810104000100u, std::string_view{"尻別川(北海道道央)", 26}},

    {810105000100u, std::string_view{"後志利別川(北海道道南)", 32}},

    {810106000100u, std::string_view{"鵡川(北海道道南)", 23}},

    {810107000100u, std::string_view{"沙流川(北海道道南)", 26}},

    {810108000100u, std::string_view{"十勝川(北海道道東)", 26}},

    {810108003400u, std::string_view{"利別川(北海道道東)", 26}},

    {810108010400u, std::string_view{"途別川(北海道道東)", 26}},

    {810108010401u, std::string_view{"十勝川水系途別川上流(北海道道東)", 47}},

    {810108011400u, std::string_view{"札内川(北海道道東)", 26}},

    {810108013900u, std::string_view{"音更川(北海道道東)", 26}},

    {810108016600u, std::string_view{"十勝川水系美生川(北海道道東)", 41}},

    {810108017400u, std::string_view{"十勝川水系芽室川(北海道道東)", 41}},

    {810109000100u, std::string_view{"釧路川・新釧路川(北海道道東)", 41}},

    {810110000100u, std::string_view{"網走川(北海道道東)", 26}},

    {810110001000u, std::string_view{"美幌川(北海道道東)", 26}},

    {810111000100u, std::string_view{"常呂川(北海道道東)", 26}},

    {810111002400u, std::string_view{"無加川(北海道道東)", 26}},

    {810112000100u, std::string_view{"湧別川(北海道道東)", 26}},

    {810113000100u, std::string_view{"渚滑川(北海道道東)", 26}},

    {819999999999u, std::string_view{"北海道のその他の河川", 30}},

    {820201000101u, std::string_view{"阿武隈川上流(福島県・宮城県)", 41}},

    {820201000102u, std::string_view{"阿武隈川下流(宮城県)", 29}},

    {820201000400u, std::string_view{"白石川(宮城県)", 20}},

    {820201009900u, std::string_view{"荒川(福島県)", 17}},

    {820202000100u, std::string_view{"名取川(宮城県)", 20}},

    {820202001100u, std::string_view{"広瀬川(宮城県)", 20}},

    {820203000100u, std::string_view{"鳴瀬川(宮城県)", 20}},

    {820203000400u, std::string_view{"吉田川(宮城県)", 20}},

    {820204000101u, std::string_view{"北上川上流(岩手県)", 26}},

    {820204000102u, std::string_view{"北上川下流(宮城県)", 26}},

    {820204001800u, std::string_view{"旧北上川(宮城県)", 23}},

    {820204001900u, std::string_view{"迫川(宮城県)", 17}},

    {820204007100u, std::string_view{"江合川(宮城県)", 20}},

    {820204035600u, std::string_view{"猿ヶ石川(岩手県)", 23}},

    {820204048200u, std::string_view{"雫石川(岩手県)", 20}},

    {820205000102u, std::string_view{"馬淵川下流(青森県)", 26}},

    {820205000103u, std::string_view{"馬淵川中流(青森県)", 26}},

    {820206000100u, std::string_view{"高瀬川(小川原湖)(青森県)", 34}},

    {820207000100u, std::string_view{"岩木川(青森県)", 20}},

    {820207003500u, std::string_view{"十川(青森県)", 17}},

    {820207006101u, std::string_view{"平川上流(青森県)", 23}},

    {820207006102u, std::string_view{"平川下流(青森県)", 23}},

    {820208000100u, std::string_view{"米代川(秋田県)", 20}},

    {820209000101u, std::string_view{"雄物川上流(秋田県)", 26}},

    {820209000102u, std::string_view{"雄物川下流(秋田県)", 26}},

    {820209000400u, std::string_view{"太平川(秋田県)", 20}},

    {820209005500u, std::string_view{"玉川(秋田県)", 17}},

    {820209018700u, std::string_view{"皆瀬川(秋田県)", 20}},

    {820210000100u, std::string_view{"子吉川(秋田県)", 20}},

    {820211000101u, std::string_view{"最上川上流(山形県)", 26}},

    {820211000102u, std::string_view{"最上川下流(山形県)", 26}},

    {820211000103u, std::string_view{"最上川中流(山形県)", 26}},

    {820211007300u, std::string_view{"鮭川(山形県)", 17}},

    {820211017000u, std::string_view{"最上小国川(山形県)", 26}},

    {820211022100u, std::string_view{"丹生川(山形県)", 20}},

    {820211030701u, std::string_view{"須川上流(山形県)", 23}},

    {820211030702u, std::string_view{"須川下流(山形県)", 23}},

    {820211048700u, std::string_view{"屋代川(山形県)", 20}},

    {820212000100u, std::string_view{"赤川(山形県)", 17}},

    {820212000200u, std::string_view{"大山川(山形県)", 20}},

    {829999999999u, std::string_view{"東北地方のその他の河川", 33}},

    {830301000100u, std::string_view{"久慈川(茨城県)", 20}},

    {830302000100u, std::string_view{"那珂川(栃木県・茨城県)", 32}},

    {830302000101u, std::string_view{"那珂川上流部(栃木県)", 29}},

    {830302008300u, std::string_view{"逆川(栃木県)", 17}},

    {830302009400u, std::string_view{"荒川(栃木県)", 17}},

    {830302014300u, std::string_view{"箒川(栃木県)", 17}},

    {830302014700u, std::string_view{"蛇尾川(栃木県)", 20}},

    {830302018300u, std::string_view{"余笹川(栃木県)", 20}},

    {830303000101u, std::string_view{"利根川上流部(群馬県・茨城県・千葉県・埼玉県)", 65}},

    {830303000102u, std::string_view{"利根川下流部(茨城県・千葉県)", 41}},

    {830303000103u, std::string_view{"利根川中流部(茨城県・千葉県)", 41}},

    {830303002800u, std::string_view{"霞ヶ浦・北浦(茨城県・千葉県)", 41}},

    {830303004600u, std::string_view{"桜川(茨城県)", 17}},

    {830303015200u, std::string_view{"小貝川(栃木県・茨城県)", 32}},

    {830303015201u, std::string_view{"小貝川上流部(栃木県)", 29}},

    {830303017900u, std::string_view{"五行川(栃木県)", 20}},

    {830303020300u, std::string_view{"鬼怒川(栃木県・茨城県)", 32}},

    {830303021100u, std::string_view{"田川(栃木県)", 17}},

    {830303030400u, std::string_view{"江戸川(茨城県・埼玉県・東京都・千葉県)", 56}},

    {830303033900u, std::string_view{"中川(埼玉県・東京都)", 29}},

    {830303033903u, std::string_view{"中川中流部(埼玉県)", 26}},

    {830303036900u, std::string_view{"元荒川(埼玉県)", 20}},

    {830303039200u, std::string_view{"新方川(埼玉県)", 20}},

    {830303039800u, std::string_view{"大落古利根川(埼玉県)", 29}},

    {830303043600u, std::string_view{"綾瀬川(谷古宇区間)(埼玉県・東京都)", 49}},

    {830303043603u, std::string_view{"綾瀬川中流部(一の橋区間)(埼玉県)", 46}},

    {830303046101u, std::string_view{"渡良瀬川上流部(群馬県・栃木県)", 44}},

    {830303046102u, std::string_view{"渡良瀬川下流部(栃木県・茨城県・群馬県)", 56}},

    {830303048000u, std::string_view{"思川(栃木県)", 17}},

    {830303048100u, std::string_view{"姿川(栃木県)", 17}},

    {830303049400u, std::string_view{"黒川(栃木県)", 17}},

    {830303051700u, std::string_view{"永野川(栃木県)", 20}},

    {830303053000u, std::string_view{"秋山川(栃木県)", 20}},

    {830303054800u, std::string_view{"袋川(栃木県)", 17}},

    {830303060000u, std::string_view{"石田川(群馬県・埼玉県)", 32}},

    {830303068900u, std::string_view{"烏川流域(群馬県・埼玉県)", 35}},

    {830303069600u, std::string_view{"神流川(群馬県・埼玉県)", 32}},

    {830304000100u, std::string_view{"荒川(埼玉県・東京都)", 29}},

    {830304000300u, std::string_view{"芝川・新芝川(埼玉県・東京都)", 41}},

    {830304001200u, std::string_view{"新河岸川(埼玉県)", 23}},

    {830304003200u, std::string_view{"石神井川(東京都)", 23}},

    {830304004400u, std::string_view{"神田川(東京都)", 20}},

    {830304004700u, std::string_view{"妙正寺川(東京都)", 23}},

    {830304004900u, std::string_view{"善福寺川(東京都)", 23}},

    {830304006403u, std::string_view{"入間川中流部(埼玉県)", 29}},

    {830304007000u, std::string_view{"越辺川・都幾川・高麗川(埼玉県)", 44}},

    {830304007100u, std::string_view{"入間川・小畔川(埼玉県)", 32}},

    {830305000100u, std::string_view{"多摩川(東京都・神奈川県)", 35}},

    {830305000500u, std::string_view{"野川・仙川(東京都)", 26}},

    {830305002000u, std::string_view{"浅川(東京都)", 17}},

    {830306000100u, std::string_view{"鶴見川(神奈川県)", 23}},

    {830307000102u, std::string_view{"相模川下流(神奈川県)", 29}},

    {830307000103u, std::string_view{"相模川中流(神奈川県)", 29}},

    {830308000100u, std::string_view{"富士川(釜無川を含む)(山梨県・静岡県)", 52}},

    {830308039500u, std::string_view{"笛吹川(山梨県)", 20}},

    {830308045500u, std::string_view{"荒川(山梨県)", 17}},

    {830308065700u, std::string_view{"塩川(山梨県)", 17}},

    {839999999999u, std::string_view{"関東地方のその他の河川", 33}},

    {840401000100u, std::string_view{"荒川(新潟県)", 17}},

    {840402000100u, std::string_view{"阿賀野川(新潟県)", 23}},

    {840402000101u, std::string_view{"阿賀川(福島県)", 20}},

    {840403000100u, std::string_view{"千曲川(長野県)", 20}},

    {840403000101u, std::string_view{"千曲川上流(長野県)", 26}},

    {840403000102u, std::string_view{"信濃川下流・中ノ口川(新潟県)", 41}},

    {840403000103u, std::string_view{"信濃川中流(新潟県)", 26}},

    {840403000104u, std::string_view{"信濃川水系千曲川下流(長野県)", 41}},

    {840403000105u, std::string_view{"信濃川上流(新潟県)", 26}},

    {840403023700u, std::string_view{"魚野川(新潟県)", 20}},

    {840403070500u, std::string_view{"犀川(長野県)", 17}},

    {840403070600u, std::string_view{"裾花川(長野県)", 20}},

    {840403089800u, std::string_view{"奈良井川(長野県)", 23}},

    {840404000100u, std::string_view{"関川(新潟県)", 17}},

    {840405000100u, std::string_view{"姫川(新潟県)", 17}},

    {840406000100u, std::string_view{"黒部川(富山県)", 20}},

    {840407000100u, std::string_view{"常願寺川(富山県)", 23}},

    {840408000101u, std::string_view{"宮川(岐阜県)", 17}},

    {840408000102u, std::string_view{"神通川(富山県)", 20}},

    {840409000100u, std::string_view{"庄川(富山県)", 17}},

    {840410000100u, std::string_view{"小矢部川(富山県)", 23}},

    {840411000100u, std::string_view{"手取川(石川県)", 20}},

    {840412000100u, std::string_view{"梯川(石川県)", 17}},

    {849999999999u, std::string_view{"北陸地方のその他の河川", 33}},

    {850501000100u, std::string_view{"狩野川(静岡県)", 20}},

    {850502000100u, std::string_view{"安倍川(静岡県)", 20}},

    {850503000100u, std::string_view{"大井川(静岡県)", 20}},

    {850504000100u, std::string_view{"菊川(静岡県)", 17}},

    {850505000101u, std::string_view{"天竜川上流(長野県)", 26}},

    {850505000102u, std::string_view{"天竜川下流(静岡県)", 26}},

    {850505071753u, std::string_view{"諏訪湖(長野県)", 20}},

    {850506000100u, std::string_view{"豊川及び豊川放水路(愛知県)", 38}},

    {850507000100u, std::string_view{"矢作川(愛知県)", 20}},

    {850508000100u, std::string_view{"庄内川(岐阜県・愛知県)", 32}},

    {850508000200u, std::string_view{"新川(愛知県)", 17}},

    {850509000102u, std::string_view{"木曽川下流(愛知県・岐阜県・三重県)", 50}},

    {850509000103u, std::string_view{"木曽川中流(岐阜県・愛知県)", 38}},

    {850509000202u, std::string_view{"揖斐川下流(岐阜県・三重県)", 38}},

    {850509000203u, std::string_view{"揖斐川中流(岐阜県)", 26}},

    {850509000401u, std::string_view{"長良川上流(岐阜県)", 26}},

    {850509000402u, std::string_view{"長良川下流(岐阜県・愛知県・三重県)", 50}},

    {850509000403u, std::string_view{"長良川中流(岐阜県)", 26}},

    {850509025500u, std::string_view{"飛騨川(岐阜県)", 20}},

    {850510000100u, std::string_view{"鈴鹿川及び鈴鹿川派川(三重県)", 41}},

    {850511000100u, std::string_view{"雲出川及び雲出古川(三重県)", 38}},

    {850512000100u, std::string_view{"櫛田川(三重県)", 20}},

    {850513000100u, std::string_view{"宮川(三重県)", 17}},

    {859999999999u, std::string_view{"中部地方のその他の河川", 33}},

    {860601000102u, std::string_view{"熊野川下流(三重県・和歌山県)", 41}},

    {860601000103u, std::string_view{"熊野川中流(本宮区間)(和歌山県)", 43}},

    {860601000105u, std::string_view{"熊野川中流(日足区間)(和歌山県)", 43}},

    {860602000100u, std::string_view{"紀の川(奈良県・和歌山県)", 35}},

    {860603000101u, std::string_view{"大和川上流(奈良県・大阪府)", 38}},

    {860603000102u, std::string_view{"大和川下流(奈良県・大阪府)", 38}},

    {860603001300u, std::string_view{"石川(大阪府)", 17}},

    {860604000101u, std::string_view{"瀬田川(滋賀県)", 20}},

    {860604000102u, std::string_view{"淀川(京都府・大阪府)", 29}},

    {860604000103u, std::string_view{"宇治川(京都府・大阪府)", 32}},

    {860604000600u, std::string_view{"寝屋川流域(大阪府)", 26}},

    {860604004700u, std::string_view{"神崎川・安威川(大阪府)", 32}},

    {860604007300u, std::string_view{"猪名川(大阪府・兵庫県)", 32}},

    {860604016702u, std::string_view{"桂川下流(京都府・大阪府)", 35}},

    {860604016703u, std::string_view{"桂川中流・園部川(京都府)", 35}},

    {860604018200u, std::string_view{"鴨川・高野川(京都府)", 29}},

    {860604037101u, std::string_view{"木津川上流(三重県・京都府)", 38}},

    {860604037102u, std::string_view{"木津川下流(京都府)", 26}},

    {860604051600u, std::string_view{"名張川(三重県・奈良県)", 32}},

    {860604086300u, std::string_view{"琵琶湖(滋賀県)", 20}},

    {860604101200u, std::string_view{"姉川(滋賀県)", 17}},

    {860604101300u, std::string_view{"高時川(滋賀県)", 20}},

    {860604120300u, std::string_view{"日野川(滋賀県)", 20}},

    {860604127501u, std::string_view{"野洲川上流(滋賀県)", 26}},

    {860604127502u, std::string_view{"野洲川下流(滋賀県)", 26}},

    {860604131100u, std::string_view{"杣川(滋賀県)", 17}},

    {860605000101u, std::string_view{"加古川上流(兵庫県)", 26}},

    {860605000102u, std::string_view{"加古川下流(兵庫県)", 26}},

    {860606000101u, std::string_view{"揖保川上流(兵庫県)", 26}},

    {860606000102u, std::string_view{"揖保川下流(兵庫県)", 26}},

    {860607000100u, std::string_view{"九頭竜川(福井県)", 23}},

    {860607000200u, std::string_view{"竹田川(福井県)", 20}},

    {860607001902u, std::string_view{"日野川下流(福井県)", 26}},

    {860607001903u, std::string_view{"日野川中流(福井県)", 26}},

    {860607002200u, std::string_view{"足羽川(福井県)", 20}},

    {860608000100u, std::string_view{"北川(福井県)", 17}},

    {860609000102u, std::string_view{"由良川下流(京都府)", 26}},

    {860609000103u, std::string_view{"由良川中流(京都府)", 26}},

    {860610000100u, std::string_view{"円山川(兵庫県)", 20}},

    {860610002600u, std::string_view{"出石川(兵庫県)", 20}},

    {869999999999u, std::string_view{"近畿地方のその他の河川", 33}},

    {870701000100u, std::string_view{"千代川(鳥取県)", 20}},

    {870701000900u, std::string_view{"袋川・新袋川(鳥取県)", 29}},

    {870702000100u, std::string_view{"天神川(鳥取県)", 20}},

    {870702000300u, std::string_view{"小鴨川(鳥取県)", 20}},

    {870702000400u, std::string_view{"国府川(鳥取県)", 20}},

    {870703000100u, std::string_view{"日野川(鳥取県)", 20}},

    {870703000300u, std::string_view{"法勝寺川(鳥取県)", 23}},

    {870704000100u, std::string_view{"斐伊川(島根県)", 20}},

    {870704002800u, std::string_view{"飯梨川(島根県)", 20}},

    {870704024400u, std::string_view{"神戸川(島根県)", 20}},

    {870705000101u, std::string_view{"江の川上流(広島県・島根県)", 38}},

    {870705000102u, std::string_view{"江の川下流(広島県・島根県)", 38}},

    {870705015700u, std::string_view{"神野瀬川(広島県)", 23}},

    {870705016300u, std::string_view{"馬洗川(広島県)", 20}},

    {870705016400u, std::string_view{"西城川(広島県)", 20}},

    {870706000100u, std::string_view{"高津川(島根県)", 20}},

    {870706001700u, std::string_view{"匹見川(島根県)", 20}},

    {870707000100u, std::string_view{"佐波川(山口県)", 20}},

    {870708000100u, std::string_view{"小瀬川(広島県・山口県)", 32}},

    {870709000101u, std::string_view{"太田川上流(広島県)", 26}},

    {870709000102u, std::string_view{"太田川下流(広島県)", 26}},

    {870709002900u, std::string_view{"三篠川(広島県)", 20}},

    {870709004700u, std::string_view{"根谷川(広島県)", 20}},

    {870710000100u, std::string_view{"芦田川(広島県)", 20}},

    {870710001100u, std::string_view{"高屋川(広島県)", 20}},

    {870711000100u, std::string_view{"高梁川(岡山県)", 20}},

    {870711000500u, std::string_view{"小田川(岡山県)", 20}},

    {870712000100u, std::string_view{"旭川(岡山県)", 17}},

    {870712000103u, std::string_view{"旭川水系旭川中流部(岡山県)", 38}},

    {870712000400u, std::string_view{"百間川(岡山県)", 20}},

    {870713000100u, std::string_view{"吉井川(岡山県)", 20}},

    {870713002800u, std::string_view{"金剛川(岡山県)", 20}},

    {879999999999u, std::string_view{"中国地方のその他の河川", 33}},

    {880801000100u, std::string_view{"重信川(愛媛県)", 20}},

    {880802000100u, std::string_view{"肱川(愛媛県)", 17}},

    {880803000100u, std::string_view{"四万十川(高知県)", 23}},

    {880804000100u, std::string_view{"仁淀川(高知県)", 20}},

    {880805000100u, std::string_view{"物部川(高知県)", 20}},

    {880806000100u, std::string_view{"那賀川(徳島県)", 20}},

    {880807000100u, std::string_view{"吉野川(徳島県)", 20}},

    {880808000100u, std::string_view{"土器川(香川県)", 20}},

    {889999999999u, std::string_view{"四国地方のその他の河川", 33}},

    {890901000101u, std::string_view{"遠賀川上流部(福岡県)", 29}},

    {890901000102u, std::string_view{"遠賀川下流部(福岡県)", 29}},

    {890901010300u, std::string_view{"彦山川(福岡県)", 20}},

    {890902000100u, std::string_view{"松浦川(佐賀県)", 20}},

    {890902001300u, std::string_view{"徳須恵川(佐賀県)", 23}},

    {890902004900u, std::string_view{"厳木川(佐賀県)", 20}},

    {890903000100u, std::string_view{"本明川(長崎県)", 20}},

    {890904000100u, std::string_view{"六角川(佐賀県)", 20}},

    {890904000300u, std::string_view{"牛津川(佐賀県)", 20}},

    {890905000100u, std::string_view{"嘉瀬川(佐賀県)", 20}},

    {890906000102u, std::string_view{"筑後川下流部(福岡県・佐賀県)", 41}},

    {890906000104u, std::string_view{"筑後川上中流部(大分県・福岡県)", 44}},

    {890907000100u, std::string_view{"矢部川(福岡県)", 20}},

    {890908000100u, std::string_view{"菊池川水系(熊本県)", 26}},

    {890909000100u, std::string_view{"白川(熊本県)", 17}},

    {890910000100u, std::string_view{"緑川水系(熊本県)", 23}},

    {890911000100u, std::string_view{"球磨川(熊本県)", 20}},

    {890912000101u, std::string_view{"川内川上流部(宮崎県・鹿児島県)", 44}},

    {890912000102u, std::string_view{"川内川下流部(鹿児島県)", 32}},

    {890913000100u, std::string_view{"肝属川水系(鹿児島県)", 29}},

    {890914000101u, std::string_view{"大淀川上流部(宮崎県)", 29}},

    {890914000102u, std::string_view{"大淀川下流部(宮崎県)", 29}},

    {890914003300u, std::string_view{"本庄川(宮崎県)", 20}},

    {890915000100u, std::string_view{"小丸川(宮崎県)", 20}},

    {890916000100u, std::string_view{"五ヶ瀬川・大瀬川(宮崎県)", 35}},

    {890917000100u, std::string_view{"番匠川(大分県)", 20}},

    {890918000100u, std::string_view{"大野川水系(大分県)", 26}},

    {890919000100u, std::string_view{"大分川(大分県)", 20}},

    {890919001100u, std::string_view{"七瀬川(大分県)", 20}},

    {890920000101u, std::string_view{"山国川上流部(大分県・福岡県)", 41}},

    {890920000102u, std::string_view{"山国川下流部(大分県・福岡県)", 41}},

    {899999999999u, std::string_view{"九州地方のその他の河川", 33}},
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_flood_forecast_region_lookup(uint64_t id) {
    uint16_t lo = 0, hi = 392;
    while (lo < hi) {
        uint16_t mid = static_cast<uint16_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_FLOOD_FORECAST_REGION_TABLE[mid].id == id) return QZSS_DCR_JMA_FLOOD_FORECAST_REGION_TABLE[mid].label;
        if (QZSS_DCR_JMA_FLOOD_FORECAST_REGION_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_flood_forecast_region_lookup(uint64_t id) {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
