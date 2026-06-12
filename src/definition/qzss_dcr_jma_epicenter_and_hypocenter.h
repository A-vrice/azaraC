#pragma once
// AUTO-GENERATED from azarashi 0.16.1 with CI-CD
// Source module : qzss_dcr_jma_epicenter_and_hypocenter
// Variable      : qzss_dcr_jma_epicenter_and_hypocenter
// Entries       : 345
// Strategy      : binary_search

#include <cstdint>
#include <optional>
#include <string_view>
#include "../azaraC.h"

namespace azaraC {
namespace def {

#if ((AZARAC_ENABLE_EEW || AZARAC_ENABLE_HYPOCENTER))

struct QZSS_DCR_JMA_EPICENTER_AND_HYPOCENTER_Entry { uint16_t id; std::string_view label; };
inline constexpr QZSS_DCR_JMA_EPICENTER_AND_HYPOCENTER_Entry QZSS_DCR_JMA_EPICENTER_AND_HYPOCENTER_TABLE[] = {
    {0u, std::string_view{"未設定(北西太平洋津波情報)", 38}},

    {11u, std::string_view{"北海道地方", 15}},

    {12u, std::string_view{"東北地方", 12}},

    {13u, std::string_view{"北陸地方", 12}},

    {14u, std::string_view{"関東甲信地方", 18}},

    {15u, std::string_view{"小笠原地方", 15}},

    {16u, std::string_view{"東海地方", 12}},

    {17u, std::string_view{"近畿地方", 12}},

    {18u, std::string_view{"中国地方", 12}},

    {19u, std::string_view{"四国地方", 12}},

    {20u, std::string_view{"九州地方", 12}},

    {21u, std::string_view{"沖縄地方", 12}},

    {100u, std::string_view{"石狩地方北部", 18}},

    {101u, std::string_view{"石狩地方中部", 18}},

    {102u, std::string_view{"石狩地方南部", 18}},

    {105u, std::string_view{"渡島地方北部", 18}},

    {106u, std::string_view{"渡島地方東部", 18}},

    {107u, std::string_view{"渡島地方西部", 18}},

    {110u, std::string_view{"檜山地方", 12}},

    {115u, std::string_view{"後志地方北部", 18}},

    {116u, std::string_view{"後志地方東部", 18}},

    {117u, std::string_view{"後志地方西部", 18}},

    {120u, std::string_view{"空知地方北部", 18}},

    {121u, std::string_view{"空知地方中部", 18}},

    {122u, std::string_view{"空知地方南部", 18}},

    {125u, std::string_view{"上川地方北部", 18}},

    {126u, std::string_view{"上川地方中部", 18}},

    {127u, std::string_view{"上川地方南部", 18}},

    {130u, std::string_view{"留萌地方中北部", 21}},

    {131u, std::string_view{"留萌地方南部", 18}},

    {135u, std::string_view{"宗谷地方北部", 18}},

    {136u, std::string_view{"宗谷地方南部", 18}},

    {140u, std::string_view{"網走地方", 12}},

    {141u, std::string_view{"北見地方", 12}},

    {142u, std::string_view{"紋別地方", 12}},

    {145u, std::string_view{"胆振地方西部", 18}},

    {146u, std::string_view{"胆振地方中東部", 21}},

    {150u, std::string_view{"日高地方西部", 18}},

    {151u, std::string_view{"日高地方中部", 18}},

    {152u, std::string_view{"日高地方東部", 18}},

    {155u, std::string_view{"十勝地方北部", 18}},

    {156u, std::string_view{"十勝地方中部", 18}},

    {157u, std::string_view{"十勝地方南部", 18}},

    {160u, std::string_view{"釧路地方北部", 18}},

    {161u, std::string_view{"釧路地方中南部", 21}},

    {165u, std::string_view{"根室地方北部", 18}},

    {166u, std::string_view{"根室地方中部", 18}},

    {167u, std::string_view{"根室地方南部", 18}},

    {180u, std::string_view{"北海道南西沖", 18}},

    {181u, std::string_view{"北海道西方沖", 18}},

    {182u, std::string_view{"石狩湾", 9}},

    {183u, std::string_view{"北海道北西沖", 18}},

    {184u, std::string_view{"宗谷海峡", 12}},

    {186u, std::string_view{"国後島付近", 15}},

    {187u, std::string_view{"択捉島付近", 15}},

    {188u, std::string_view{"北海道東方沖", 18}},

    {189u, std::string_view{"根室半島南東沖", 21}},

    {190u, std::string_view{"釧路沖", 9}},

    {191u, std::string_view{"十勝沖", 9}},

    {192u, std::string_view{"浦河沖", 9}},

    {193u, std::string_view{"苫小牧沖", 12}},

    {194u, std::string_view{"内浦湾", 9}},

    {195u, std::string_view{"宗谷東方沖", 15}},

    {196u, std::string_view{"網走沖", 9}},

    {197u, std::string_view{"択捉島南東沖", 18}},

    {200u, std::string_view{"青森県津軽北部", 21}},

    {201u, std::string_view{"青森県津軽南部", 21}},

    {202u, std::string_view{"青森県三八上北地方", 27}},

    {203u, std::string_view{"青森県下北地方", 21}},

    {210u, std::string_view{"岩手県沿岸北部", 21}},

    {211u, std::string_view{"岩手県沿岸南部", 21}},

    {212u, std::string_view{"岩手県内陸北部", 21}},

    {213u, std::string_view{"岩手県内陸南部", 21}},

    {220u, std::string_view{"宮城県北部", 15}},

    {221u, std::string_view{"宮城県南部", 15}},

    {222u, std::string_view{"宮城県中部", 15}},

    {230u, std::string_view{"秋田県沿岸北部", 21}},

    {231u, std::string_view{"秋田県沿岸南部", 21}},

    {232u, std::string_view{"秋田県内陸北部", 21}},

    {233u, std::string_view{"秋田県内陸南部", 21}},

    {240u, std::string_view{"山形県庄内地方", 21}},

    {241u, std::string_view{"山形県最上地方", 21}},

    {242u, std::string_view{"山形県村山地方", 21}},

    {243u, std::string_view{"山形県置賜地方", 21}},

    {250u, std::string_view{"福島県中通り", 18}},

    {251u, std::string_view{"福島県浜通り", 18}},

    {252u, std::string_view{"福島県会津", 15}},

    {280u, std::string_view{"津軽海峡", 12}},

    {281u, std::string_view{"山形県沖", 12}},

    {282u, std::string_view{"秋田県沖", 12}},

    {283u, std::string_view{"青森県西方沖", 18}},

    {284u, std::string_view{"陸奥湾", 9}},

    {285u, std::string_view{"青森県東方沖", 18}},

    {286u, std::string_view{"岩手県沖", 12}},

    {287u, std::string_view{"宮城県沖", 12}},

    {288u, std::string_view{"三陸沖", 9}},

    {289u, std::string_view{"福島県沖", 12}},

    {300u, std::string_view{"茨城県北部", 15}},

    {301u, std::string_view{"茨城県南部", 15}},

    {309u, std::string_view{"千葉県南東沖", 18}},

    {310u, std::string_view{"栃木県北部", 15}},

    {311u, std::string_view{"栃木県南部", 15}},

    {320u, std::string_view{"群馬県北部", 15}},

    {321u, std::string_view{"群馬県南部", 15}},

    {330u, std::string_view{"埼玉県北部", 15}},

    {331u, std::string_view{"埼玉県南部", 15}},

    {332u, std::string_view{"埼玉県秩父地方", 21}},

    {340u, std::string_view{"千葉県北東部", 18}},

    {341u, std::string_view{"千葉県北西部", 18}},

    {342u, std::string_view{"千葉県南部", 15}},

    {349u, std::string_view{"房総半島南方沖", 21}},

    {350u, std::string_view{"東京都２３区", 18}},

    {351u, std::string_view{"東京都多摩東部", 21}},

    {352u, std::string_view{"東京都多摩西部", 21}},

    {360u, std::string_view{"神奈川県東部", 18}},

    {361u, std::string_view{"神奈川県西部", 18}},

    {370u, std::string_view{"新潟県上越地方", 21}},

    {371u, std::string_view{"新潟県中越地方", 21}},

    {372u, std::string_view{"新潟県下越地方", 21}},

    {378u, std::string_view{"新潟県下越沖", 18}},

    {379u, std::string_view{"新潟県上中越沖", 21}},

    {380u, std::string_view{"富山県東部", 15}},

    {381u, std::string_view{"富山県西部", 15}},

    {390u, std::string_view{"石川県能登地方", 21}},

    {391u, std::string_view{"石川県加賀地方", 21}},

    {400u, std::string_view{"福井県嶺北", 15}},

    {401u, std::string_view{"福井県嶺南", 15}},

    {411u, std::string_view{"山梨県中・西部", 21}},

    {412u, std::string_view{"山梨県東部・富士五湖", 30}},

    {420u, std::string_view{"長野県北部", 15}},

    {421u, std::string_view{"長野県中部", 15}},

    {422u, std::string_view{"長野県南部", 15}},

    {430u, std::string_view{"岐阜県飛騨地方", 21}},

    {431u, std::string_view{"岐阜県美濃東部", 21}},

    {432u, std::string_view{"岐阜県美濃中西部", 24}},

    {440u, std::string_view{"静岡県伊豆地方", 21}},

    {441u, std::string_view{"静岡県東部", 15}},

    {442u, std::string_view{"静岡県中部", 15}},

    {443u, std::string_view{"静岡県西部", 15}},

    {450u, std::string_view{"愛知県東部", 15}},

    {451u, std::string_view{"愛知県西部", 15}},

    {460u, std::string_view{"三重県北部", 15}},

    {461u, std::string_view{"三重県中部", 15}},

    {462u, std::string_view{"三重県南部", 15}},

    {469u, std::string_view{"三重県南東沖", 18}},

    {471u, std::string_view{"茨城県沖", 12}},

    {472u, std::string_view{"関東東方沖", 15}},

    {473u, std::string_view{"千葉県東方沖", 18}},

    {475u, std::string_view{"八丈島東方沖", 18}},

    {476u, std::string_view{"八丈島近海", 15}},

    {477u, std::string_view{"東京湾", 9}},

    {478u, std::string_view{"相模湾", 9}},

    {480u, std::string_view{"伊豆大島近海", 18}},

    {481u, std::string_view{"伊豆半島東方沖", 21}},

    {482u, std::string_view{"三宅島近海", 15}},

    {483u, std::string_view{"新島・神津島近海", 24}},

    {485u, std::string_view{"駿河湾", 9}},

    {486u, std::string_view{"駿河湾南方沖", 18}},

    {487u, std::string_view{"遠州灘", 9}},

    {489u, std::string_view{"三河湾", 9}},

    {490u, std::string_view{"伊勢湾", 9}},

    {492u, std::string_view{"若狭湾", 9}},

    {493u, std::string_view{"福井県沖", 12}},

    {494u, std::string_view{"石川県西方沖", 18}},

    {495u, std::string_view{"能登半島沖", 15}},

    {497u, std::string_view{"富山湾", 9}},

    {498u, std::string_view{"佐渡付近", 12}},

    {499u, std::string_view{"東海道南方沖", 18}},

    {500u, std::string_view{"滋賀県北部", 15}},

    {501u, std::string_view{"滋賀県南部", 15}},

    {510u, std::string_view{"京都府北部", 15}},

    {511u, std::string_view{"京都府南部", 15}},

    {520u, std::string_view{"大阪府北部", 15}},

    {521u, std::string_view{"大阪府南部", 15}},

    {530u, std::string_view{"兵庫県北部", 15}},

    {531u, std::string_view{"兵庫県南東部", 18}},

    {532u, std::string_view{"兵庫県南西部", 18}},

    {540u, std::string_view{"奈良県", 9}},

    {550u, std::string_view{"和歌山県北部", 18}},

    {551u, std::string_view{"和歌山県南部", 18}},

    {560u, std::string_view{"鳥取県東部", 15}},

    {562u, std::string_view{"鳥取県中部", 15}},

    {563u, std::string_view{"鳥取県西部", 15}},

    {570u, std::string_view{"島根県東部", 15}},

    {571u, std::string_view{"島根県西部", 15}},

    {580u, std::string_view{"岡山県北部", 15}},

    {581u, std::string_view{"岡山県南部", 15}},

    {590u, std::string_view{"広島県北部", 15}},

    {591u, std::string_view{"広島県南東部", 18}},

    {592u, std::string_view{"広島県南西部", 18}},

    {600u, std::string_view{"徳島県北部", 15}},

    {601u, std::string_view{"徳島県南部", 15}},

    {610u, std::string_view{"香川県東部", 15}},

    {611u, std::string_view{"香川県西部", 15}},

    {620u, std::string_view{"愛媛県東予", 15}},

    {621u, std::string_view{"愛媛県中予", 15}},

    {622u, std::string_view{"愛媛県南予", 15}},

    {630u, std::string_view{"高知県東部", 15}},

    {631u, std::string_view{"高知県中部", 15}},

    {632u, std::string_view{"高知県西部", 15}},

    {673u, std::string_view{"土佐湾", 9}},

    {674u, std::string_view{"紀伊水道", 12}},

    {675u, std::string_view{"大阪湾", 9}},

    {676u, std::string_view{"播磨灘", 9}},

    {677u, std::string_view{"瀬戸内海中部", 18}},

    {678u, std::string_view{"安芸灘", 9}},

    {679u, std::string_view{"周防灘", 9}},

    {680u, std::string_view{"伊予灘", 9}},

    {681u, std::string_view{"豊後水道", 12}},

    {682u, std::string_view{"山口県北西沖", 18}},

    {683u, std::string_view{"島根県沖", 12}},

    {684u, std::string_view{"鳥取県沖", 12}},

    {685u, std::string_view{"隠岐島近海", 15}},

    {686u, std::string_view{"兵庫県北方沖", 18}},

    {687u, std::string_view{"京都府沖", 12}},

    {688u, std::string_view{"淡路島付近", 15}},

    {689u, std::string_view{"和歌山県南方沖", 21}},

    {700u, std::string_view{"山口県北部", 15}},

    {702u, std::string_view{"山口県西部", 15}},

    {703u, std::string_view{"山口県東部", 15}},

    {704u, std::string_view{"山口県中部", 15}},

    {710u, std::string_view{"福岡県福岡地方", 21}},

    {711u, std::string_view{"福岡県北九州地方", 24}},

    {712u, std::string_view{"福岡県筑豊地方", 21}},

    {713u, std::string_view{"福岡県筑後地方", 21}},

    {720u, std::string_view{"佐賀県北部", 15}},

    {721u, std::string_view{"佐賀県南部", 15}},

    {730u, std::string_view{"長崎県北部", 15}},

    {731u, std::string_view{"長崎県南西部", 18}},

    {732u, std::string_view{"長崎県島原半島", 21}},

    {740u, std::string_view{"熊本県阿蘇地方", 21}},

    {741u, std::string_view{"熊本県熊本地方", 21}},

    {742u, std::string_view{"熊本県球磨地方", 21}},

    {743u, std::string_view{"熊本県天草・芦北地方", 30}},

    {750u, std::string_view{"大分県北部", 15}},

    {751u, std::string_view{"大分県中部", 15}},

    {752u, std::string_view{"大分県南部", 15}},

    {753u, std::string_view{"大分県西部", 15}},

    {760u, std::string_view{"宮崎県北部平野部", 24}},

    {761u, std::string_view{"宮崎県北部山沿い", 24}},

    {762u, std::string_view{"宮崎県南部平野部", 24}},

    {763u, std::string_view{"宮崎県南部山沿い", 24}},

    {770u, std::string_view{"鹿児島県薩摩地方", 24}},

    {771u, std::string_view{"鹿児島県大隅地方", 24}},

    {783u, std::string_view{"五島列島近海", 18}},

    {784u, std::string_view{"天草灘", 9}},

    {785u, std::string_view{"有明海", 9}},

    {786u, std::string_view{"橘湾", 6}},

    {787u, std::string_view{"鹿児島湾", 12}},

    {790u, std::string_view{"種子島近海", 15}},

    {791u, std::string_view{"日向灘", 9}},

    {793u, std::string_view{"奄美大島近海", 18}},

    {795u, std::string_view{"壱岐・対馬近海", 21}},

    {796u, std::string_view{"福岡県北西沖", 18}},

    {797u, std::string_view{"薩摩半島西方沖", 21}},

    {798u, std::string_view{"トカラ列島近海", 21}},

    {799u, std::string_view{"奄美大島北西沖", 21}},

    {820u, std::string_view{"大隅半島東方沖", 21}},

    {821u, std::string_view{"九州地方南東沖", 21}},

    {822u, std::string_view{"種子島南東沖", 18}},

    {823u, std::string_view{"奄美大島北東沖", 21}},

    {850u, std::string_view{"沖縄本島近海", 18}},

    {851u, std::string_view{"南大東島近海", 18}},

    {852u, std::string_view{"沖縄本島南方沖", 21}},

    {853u, std::string_view{"宮古島近海", 15}},

    {854u, std::string_view{"石垣島近海", 15}},

    {855u, std::string_view{"石垣島南方沖", 18}},

    {856u, std::string_view{"西表島付近", 15}},

    {857u, std::string_view{"与那国島近海", 18}},

    {858u, std::string_view{"沖縄本島北西沖", 21}},

    {859u, std::string_view{"宮古島北西沖", 18}},

    {860u, std::string_view{"石垣島北西沖", 18}},

    {900u, std::string_view{"台湾付近", 12}},

    {901u, std::string_view{"東シナ海", 12}},

    {902u, std::string_view{"四国沖", 9}},

    {903u, std::string_view{"鳥島近海", 12}},

    {904u, std::string_view{"鳥島東方沖", 15}},

    {905u, std::string_view{"オホーツク海南部", 24}},

    {906u, std::string_view{"サハリン西方沖", 21}},

    {907u, std::string_view{"日本海北部", 15}},

    {908u, std::string_view{"日本海中部", 15}},

    {909u, std::string_view{"日本海西部", 15}},

    {911u, std::string_view{"父島近海", 12}},

    {912u, std::string_view{"千島列島", 12}},

    {913u, std::string_view{"千島列島南東沖", 21}},

    {914u, std::string_view{"北海道南東沖", 18}},

    {915u, std::string_view{"東北地方東方沖", 21}},

    {916u, std::string_view{"小笠原諸島西方沖", 24}},

    {917u, std::string_view{"硫黄島近海", 15}},

    {918u, std::string_view{"小笠原諸島東方沖", 24}},

    {919u, std::string_view{"南海道南方沖", 18}},

    {920u, std::string_view{"薩南諸島東方沖", 21}},

    {921u, std::string_view{"本州南方沖", 15}},

    {922u, std::string_view{"サハリン南部付近", 24}},

    {930u, std::string_view{"北西太平洋", 15}},

    {932u, std::string_view{"マリアナ諸島", 18}},

    {933u, std::string_view{"黄海", 6}},

    {934u, std::string_view{"朝鮮半島南部", 18}},

    {935u, std::string_view{"朝鮮半島北部", 18}},

    {936u, std::string_view{"中国東北部", 15}},

    {937u, std::string_view{"ウラジオストク付近", 27}},

    {938u, std::string_view{"シベリア南部", 18}},

    {939u, std::string_view{"サハリン近海", 18}},

    {940u, std::string_view{"アリューシャン列島", 27}},

    {941u, std::string_view{"カムチャツカ半島付近", 30}},

    {942u, std::string_view{"北米西部", 12}},

    {943u, std::string_view{"北米中部", 12}},

    {944u, std::string_view{"北米東部", 12}},

    {945u, std::string_view{"中米", 6}},

    {946u, std::string_view{"南米西部", 12}},

    {947u, std::string_view{"南米中部", 12}},

    {948u, std::string_view{"南米東部", 12}},

    {949u, std::string_view{"北東太平洋", 15}},

    {950u, std::string_view{"南太平洋", 12}},

    {951u, std::string_view{"インドシナ半島付近", 27}},

    {952u, std::string_view{"フィリピン付近", 21}},

    {953u, std::string_view{"インドネシア付近", 24}},

    {954u, std::string_view{"グアム付近", 15}},

    {955u, std::string_view{"ニューギニア付近", 24}},

    {956u, std::string_view{"ニュージーランド付近", 30}},

    {957u, std::string_view{"オーストラリア付近", 27}},

    {958u, std::string_view{"シベリア付近", 18}},

    {959u, std::string_view{"ロシア西部", 15}},

    {960u, std::string_view{"ロシア中部", 15}},

    {961u, std::string_view{"ロシア東部", 15}},

    {962u, std::string_view{"中央アジア", 15}},

    {963u, std::string_view{"中国西部", 12}},

    {964u, std::string_view{"中国中部", 12}},

    {965u, std::string_view{"中国東部", 12}},

    {966u, std::string_view{"インド付近", 15}},

    {967u, std::string_view{"インド洋", 12}},

    {968u, std::string_view{"中東", 6}},

    {969u, std::string_view{"ヨーロッパ西部", 21}},

    {970u, std::string_view{"ヨーロッパ中部", 21}},

    {971u, std::string_view{"ヨーロッパ東部", 21}},

    {972u, std::string_view{"地中海", 9}},

    {973u, std::string_view{"アフリカ西部", 18}},

    {974u, std::string_view{"アフリカ中部", 18}},

    {975u, std::string_view{"アフリカ東部", 18}},

    {976u, std::string_view{"北大西洋", 12}},

    {977u, std::string_view{"南大西洋", 12}},

    {978u, std::string_view{"北極付近", 12}},

    {979u, std::string_view{"南極付近", 12}},

    {999u, std::string_view{"遠地", 6}},

    {1000u, std::string_view{"その他の震央地名", 24}},
};
[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_epicenter_and_hypocenter_lookup(uint16_t id) {
    uint16_t lo = 0, hi = 345;
    while (lo < hi) {
        uint16_t mid = static_cast<uint16_t>(lo + (hi - lo) / 2);
        if (QZSS_DCR_JMA_EPICENTER_AND_HYPOCENTER_TABLE[mid].id == id) return QZSS_DCR_JMA_EPICENTER_AND_HYPOCENTER_TABLE[mid].label;
        if (QZSS_DCR_JMA_EPICENTER_AND_HYPOCENTER_TABLE[mid].id < id) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}

#else

[[nodiscard]] inline constexpr std::optional<std::string_view> qzss_dcr_jma_epicenter_and_hypocenter_lookup(uint16_t id) {
    (void)id;
    return std::nullopt;
}

#endif

} // namespace def
} // namespace azaraC
