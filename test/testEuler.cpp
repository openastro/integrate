/*
 * Copyright (c) 2018 Kartik Kumar (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include <catch2/catch.hpp>

#include <functional>
#include <limits>
#include <map>
#include <string>
#include <vector>

#include "integrate/euler.hpp"

#include "testDynamicalModels.hpp"
#include "testState.hpp"

namespace integrate
{
namespace tests
{

TEST_CASE( "Test Euler integrator for zero dynamics free function", "[euler]" )
{
    const Real initialTime = 1.0;
    const State initialState( { 1.2, 2.3, -3.6 } );
    const Real stepSize = 0.1;

    Real currentTime = initialTime;
    State currentState = initialState;

    stepEuler< Real, State >( currentTime,
                              currentState,
                              stepSize,
                              &computeZeroDynamics );

    REQUIRE( currentTime  == ( initialTime + stepSize ) );
    REQUIRE( currentState == initialState );
}

TEST_CASE( "Test Euler integrator for zero dynamics class", "[euler]" )
{
    const Real initialTime = 1.0;
    const State initialState( { 1.2, 2.3, -3.6 } );
    const Real stepSize = 0.1;

    Real currentTime = initialTime;
    State currentState = initialState;

    ZeroDynamics dynamics;
    auto stateDerivativePointer = std::bind( &ZeroDynamics::operator(),
                                             &dynamics,
                                             std::placeholders::_1,
                                             std::placeholders::_2 );
    stepEuler< Real, State >( currentTime,
                              currentState,
                              stepSize,
                              stateDerivativePointer );

    REQUIRE( currentTime  == ( initialTime + stepSize ) );
    REQUIRE( currentState == initialState );
}

TEST_CASE( "Test Euler integrator for Burden & Faires (9th ed.): Table 5.1", "[euler]" )
{
    const Real initialTime = 0.0;
    const State initialState( { 0.5 } );
    const Real stepSize = 0.2;

    Real currentTime = initialTime;
    State currentState = initialState;

    const Real testTolerance = 1.0e-7;

    std::map< Real, State > burdenFairesTable5_1Data;
    burdenFairesTable5_1Data.insert( { 0.2 , State( { 0.8000000 } ) } );
    burdenFairesTable5_1Data.insert( { 0.4 , State( { 1.1520000 } ) } );
    burdenFairesTable5_1Data.insert( { 0.6 , State( { 1.5504000 } ) } );
    burdenFairesTable5_1Data.insert( { 0.8 , State( { 1.9884800 } ) } );
    burdenFairesTable5_1Data.insert( { 1.0 , State( { 2.4581760 } ) } );
    burdenFairesTable5_1Data.insert( { 1.2 , State( { 2.9498112 } ) } );
    burdenFairesTable5_1Data.insert( { 1.4 , State( { 3.4517734 } ) } );
    burdenFairesTable5_1Data.insert( { 1.6 , State( { 3.9501281 } ) } );
    burdenFairesTable5_1Data.insert( { 1.8 , State( { 4.4281538 } ) } );
    burdenFairesTable5_1Data.insert( { 2.0 , State( { 4.8657845 } ) } );

    BurdenFaires dynamics;
    auto stateDerivativePointer = std::bind( &BurdenFaires::operator( ),
                                             &dynamics,
                                             std::placeholders::_1,
                                             std::placeholders::_2 );

    for ( const auto& pair : burdenFairesTable5_1Data )
    {
       stepEuler< Real, State >( currentTime,
                                 currentState,
                                 stepSize,
                                 stateDerivativePointer );
        REQUIRE( pair.first == Approx( currentTime ).epsilon( testTolerance ) );
        REQUIRE( pair.second[ 0 ] == Approx( currentState[ 0 ] ).epsilon( testTolerance ) );
    }
}

TEST_CASE( "Test Euler integrator for Burden & Faires (9th ed.): Table 5.1 using MATLAB",
           "[euler]" )
{
    const Real initialTime = -1.0;
    const State initialState( { 0.5 } );
    const Real stepSize = 0.01;

    Real currentTime = initialTime;
    State currentState = initialState;

    const Real testTolerance = 1.0e-13;
    const Real testMargin    = 1.0e-15;

    std::map< Real, State > matlabData;
    matlabData.insert( { -0.99, State( { 0.505 } ) } );
    matlabData.insert( { -0.98, State( { 0.510249 } ) } );
    matlabData.insert( { -0.97, State( { 0.51574749 } ) } );
    matlabData.insert( { -0.96, State( { 0.5214959649 } ) } );
    matlabData.insert( { -0.95, State( { 0.527494924549 } ) } );
    matlabData.insert( { -0.94, State( { 0.53374487379449 } ) } );
    matlabData.insert( { -0.93, State( { 0.5402463225324349 } ) } );
    matlabData.insert( { -0.92, State( { 0.546999785757759249 } ) } );
    matlabData.insert( { -0.91, State( { 0.5540057836153368415 } ) } );
    matlabData.insert( { -0.9,  State( { 0.5612648414514902099 } ) } );
    matlabData.insert( { -0.89, State( { 0.568777489866005112 } ) } );
    matlabData.insert( { -0.88, State( { 0.5765442647646651631 } ) } );
    matlabData.insert( { -0.87, State( { 0.5845657074123118148 } ) } );
    matlabData.insert( { -0.86, State( { 0.5928423644864349329 } ) } );
    matlabData.insert( { -0.85, State( { 0.6013747881312992822 } ) } );
    matlabData.insert( { -0.84, State( { 0.6101635360126122751 } ) } );
    matlabData.insert( { -0.83, State( { 0.6192091713727383978 } ) } );
    matlabData.insert( { -0.82, State( { 0.6285122630864657818 } ) } );
    matlabData.insert( { -0.81, State( { 0.6380733857173304396 } ) } );
    matlabData.insert( { -0.8,  State( { 0.647893119574503744 } ) } );
    matlabData.insert( { -0.79, State( { 0.6579720507702487814 } ) } );
    matlabData.insert( { -0.78, State( { 0.6683107712779512693 } ) } );
    matlabData.insert( { -0.77, State( { 0.6789098789907307819 } ) } );
    matlabData.insert( { -0.76, State( { 0.6897699777806380898 } ) } );
    matlabData.insert( { -0.75, State( { 0.7008916775584444707 } ) } );
    matlabData.insert( { -0.74, State( { 0.7122755943340289154 } ) } );
    matlabData.insert( { -0.73, State( { 0.7239223502773692045 } ) } );
    matlabData.insert( { -0.72, State( { 0.7358325737801428966 } ) } );
    matlabData.insert( { -0.71, State( { 0.7480068995179443255 } ) } );
    matlabData.insert( { -0.7,  State( { 0.7604459685131237688 } ) } );
    matlabData.insert( { -0.69, State( { 0.7731504281982550065 } ) } );
    matlabData.insert( { -0.68, State( { 0.7861209324802375565 } ) } );
    matlabData.insert( { -0.67, State( { 0.7993581418050399321 } ) } );
    matlabData.insert( { -0.66, State( { 0.8128627232230903314 } ) } );
    matlabData.insert( { -0.65, State( { 0.8266353504553212347 } ) } );
    matlabData.insert( { -0.64, State( { 0.8406767039598744471 } ) } );
    matlabData.insert( { -0.63, State( { 0.8549874709994731916 } ) } );
    matlabData.insert( { -0.62, State( { 0.8695683457094679235 } ) } );
    matlabData.insert( { -0.61, State( { 0.8844200291665626027 } ) } );
    matlabData.insert( { -0.6,  State( { 0.8995432294582282287 } ) } );
    matlabData.insert( { -0.59, State( { 0.914938661752810511 } ) } );
    matlabData.insert( { -0.58, State( { 0.9306070483703386161 } ) } );
    matlabData.insert( { -0.57, State( { 0.9465491188540420023 } ) } );
    matlabData.insert( { -0.56, State( { 0.9627656100425824223 } ) } );
    matlabData.insert( { -0.55, State( { 0.9792572661430082465 } ) } );
    matlabData.insert( { -0.54, State( { 0.996024838804438329 } ) } );
    matlabData.insert( { -0.53, State( { 1.013069087192482712 } ) } );
    matlabData.insert( { -0.52, State( { 1.030390778064407539 } ) } );
    matlabData.insert( { -0.51, State( { 1.047990685845051615 } ) } );
    matlabData.insert( { -0.5,  State( { 1.065869592703502131 } ) } );
    matlabData.insert( { -0.49, State( { 1.084028288630537152 } ) } );
    matlabData.insert( { -0.48, State( { 1.102467571516842524 } ) } );
    matlabData.insert( { -0.47, State( { 1.121188247232010949 } ) } );
    matlabData.insert( { -0.46, State( { 1.140191129704331059 } ) } );
    matlabData.insert( { -0.45, State( { 1.159477041001374369 } ) } );
    matlabData.insert( { -0.44, State( { 1.179046811411388113 } ) } );
    matlabData.insert( { -0.43, State( { 1.198901279525501994 } ) } );
    matlabData.insert( { -0.42, State( { 1.219041292320757014 } ) } );
    matlabData.insert( { -0.41, State( { 1.239467705243964584 } ) } );
    matlabData.insert( { -0.4,  State( { 1.26018138229640423 } ) } );
    matlabData.insert( { -0.39, State( { 1.281183196119368272 } ) } );
    matlabData.insert( { -0.38, State( { 1.302474028080561955 } ) } );
    matlabData.insert( { -0.37, State( { 1.324054768361367574 } ) } );
    matlabData.insert( { -0.36, State( { 1.34592631604498125 } ) } );
    matlabData.insert( { -0.35, State( { 1.368089579205431063 } ) } );
    matlabData.insert( { -0.34, State( { 1.390545474997485373 } ) } );
    matlabData.insert( { -0.33, State( { 1.413294929747460227 } ) } );
    matlabData.insert( { -0.32, State( { 1.436338879044934829 } ) } );
    matlabData.insert( { -0.31, State( { 1.459678267835384178 } ) } );
    matlabData.insert( { -0.3,  State( { 1.483314050513738019 } ) } );
    matlabData.insert( { -0.29, State( { 1.5072471910188754 } ) } );
    matlabData.insert( { -0.28, State( { 1.531478662929064154 } ) } );
    matlabData.insert( { -0.27, State( { 1.556009449558354795 } ) } );
    matlabData.insert( { -0.26, State( { 1.580840544053938343 } ) } );
    matlabData.insert( { -0.25, State( { 1.605972949494477726 } ) } );
    matlabData.insert( { -0.24, State( { 1.631407678989422504 } ) } );
    matlabData.insert( { -0.23, State( { 1.657145755779316729 } ) } );
    matlabData.insert( { -0.22, State( { 1.683188213337109896 } ) } );
    matlabData.insert( { -0.21, State( { 1.709536095470480995 } ) } );
    matlabData.insert( { -0.2,  State( { 1.736190456425185805 } ) } );
    matlabData.insert( { -0.19, State( { 1.763152360989437663 } ) } );
    matlabData.insert( { -0.18, State( { 1.79042288459933204 } ) } );
    matlabData.insert( { -0.17, State( { 1.81800311344532536 } ) } );
    matlabData.insert( { -0.16, State( { 1.845894144579778614 } ) } );
    matlabData.insert( { -0.15, State( { 1.8740970860255764 } ) } );
    matlabData.insert( { -0.14, State( { 1.902613056885832164 } ) } );
    matlabData.insert( { -0.13, State( { 1.931443187454690485 } ) } );
    matlabData.insert( { -0.12, State( { 1.96058861932923739 } ) } );
    matlabData.insert( { -0.11, State( { 1.990050505522529764 } ) } );
    matlabData.insert( { -0.1,  State( { 2.019830010577755062 } ) } );
    matlabData.insert( { -0.09, State( { 2.049928310683532612 } ) } );
    matlabData.insert( { -0.08, State( { 2.080346593790367939 } ) } );
    matlabData.insert( { -0.07, State( { 2.111086059728271618 } ) } );
    matlabData.insert( { -0.06, State( { 2.142147920325554334 } ) } );
    matlabData.insert( { -0.05, State( { 2.173533399528809877 } ) } );
    matlabData.insert( { -0.04, State( { 2.205243733524097976 } ) } );
    matlabData.insert( { -0.03, State( { 2.237280170859338956 } ) } );
    matlabData.insert( { -0.02, State( { 2.269643972567932346 } ) } );
    matlabData.insert( { -0.01, State( { 2.302336412293611669 } ) } );
    matlabData.insert( { 8.077935669463160887e-28, State( { 2.335358776416547786 } ) } );
    matlabData.insert( { 0.01,  State( { 2.368712364180713264 } ) } );
    matlabData.insert( { 0.02,  State( { 2.402398487822520396 } ) } );
    matlabData.insert( { 0.03,  State( { 2.4364184727007456 } ) } );
    matlabData.insert( { 0.04,  State( { 2.470773657427753056 } ) } );
    matlabData.insert( { 0.05,  State( { 2.505465394002030587 } ) } );
    matlabData.insert( { 0.06,  State( { 2.540495047942050893 } ) } );
    matlabData.insert( { 0.07,  State( { 2.575863998421471402 } ) } );
    matlabData.insert( { 0.08,  State( { 2.611573638405686116 } ) } );
    matlabData.insert( { 0.09,  State( { 2.647625374789742977 } ) } );
    matlabData.insert( { 0.1,   State( { 2.684020628537640406 } ) } );
    matlabData.insert( { 0.11,  State( { 2.720760834823016811 } ) } );
    matlabData.insert( { 0.12,  State( { 2.757847443171246979 } ) } );
    matlabData.insert( { 0.13,  State( { 2.795281917602959448 } ) } );
    matlabData.insert( { 0.14,  State( { 2.833065736778989043 } ) } );
    matlabData.insert( { 0.15,  State( { 2.871200394146778933 } ) } );
    matlabData.insert( { 0.16,  State( { 2.909687398088246723 } ) } );
    matlabData.insert( { 0.17,  State( { 2.94852827206912919 } ) } );
    matlabData.insert( { 0.18,  State( { 2.987724554789820482 } ) } );
    matlabData.insert( { 0.19,  State( { 3.027277800337718687 } ) } );
    matlabData.insert( { 0.2,   State( { 3.067189578341095873 } ) } );
    matlabData.insert( { 0.21,  State( { 3.107461474124506832 } ) } );
    matlabData.insert( { 0.22,  State( { 3.148095088865751901 } ) } );
    matlabData.insert( { 0.23,  State( { 3.18909203975440942 } ) } );
    matlabData.insert( { 0.24,  State( { 3.230453960151953514 } ) } );
    matlabData.insert( { 0.25,  State( { 3.272182499753473049 } ) } );
    matlabData.insert( { 0.26,  State( { 3.314279324751007779 } ) } );
    matlabData.insert( { 0.27,  State( { 3.356746117998517857 } ) } );
    matlabData.insert( { 0.28,  State( { 3.399584579178503036 } ) } );
    matlabData.insert( { 0.29,  State( { 3.442796424970288066 } ) } );
    matlabData.insert( { 0.3,   State( { 3.486383389219990947 } ) } );
    matlabData.insert( { 0.31,  State( { 3.530347223112190856 } ) } );
    matlabData.insert( { 0.32,  State( { 3.574689695343312765 } ) } );
    matlabData.insert( { 0.33,  State( { 3.619412592296745892 } ) } );
    matlabData.insert( { 0.34,  State( { 3.664517718219713351 } ) } );
    matlabData.insert( { 0.35,  State( { 3.710006895401910485 } ) } );
    matlabData.insert( { 0.36,  State( { 3.75588196435592959 } ) } );
    matlabData.insert( { 0.37,  State( { 3.802144783999488886 } ) } );
    matlabData.insert( { 0.38,  State( { 3.848797231839483774 } ) } );
    matlabData.insert( { 0.39,  State( { 3.895841204157878612 } ) } );
    matlabData.insert( { 0.4,   State( { 3.943278616199457398 } ) } );
    matlabData.insert( { 0.41,  State( { 3.991111402361451972 } ) } );
    matlabData.insert( { 0.42,  State( { 4.039341516385066492 } ) } );
    matlabData.insert( { 0.43,  State( { 4.087970931548917157 } ) } );
    matlabData.insert( { 0.44,  State( { 4.137001640864406329 } ) } );
    matlabData.insert( { 0.45,  State( { 4.186435657273050392 } ) } );
    matlabData.insert( { 0.46,  State( { 4.236275013845780896 } ) } );
    matlabData.insert( { 0.47,  State( { 4.286521763984238705 } ) } );
    matlabData.insert( { 0.48,  State( { 4.337177981624081092 } ) } );
    matlabData.insert( { 0.49,  State( { 4.388245761440321903 } ) } );
    matlabData.insert( { 0.5,   State( { 4.439727219054725122 } ) } );
    matlabData.insert( { 0.51,  State( { 4.491624491245272373 } ) } );
    matlabData.insert( { 0.52,  State( { 4.543939736157725097 } ) } );
    matlabData.insert( { 0.53,  State( { 4.596675133519302348 } ) } );
    matlabData.insert( { 0.54,  State( { 4.649832884854495371 } ) } );
    matlabData.insert( { 0.55,  State( { 4.703415213703040325 } ) } );
    matlabData.insert( { 0.56,  State( { 4.757424365840070728 } ) } );
    matlabData.insert( { 0.57,  State( { 4.811862609498471435 } ) } );
    matlabData.insert( { 0.58,  State( { 4.86673223559345615 } ) } );
    matlabData.insert( { 0.59,  State( { 4.922035557949390711 } ) } );
    matlabData.insert( { 0.6,   State( { 4.977774913528884618 } ) } );
    matlabData.insert( { 0.61,  State( { 5.033952662664173464 } ) } );
    matlabData.insert( { 0.62,  State( { 5.090571189290815199 } ) } );
    matlabData.insert( { 0.63,  State( { 5.147632901183723351 } ) } );
    matlabData.insert( { 0.64,  State( { 5.205140230195560585 } ) } );
    matlabData.insert( { 0.65,  State( { 5.26309563249751619 } ) } );
    matlabData.insert( { 0.66,  State( { 5.321501588822491352 } ) } );
    matlabData.insert( { 0.67,  State( { 5.380360604710716266 } ) } );
    matlabData.insert( { 0.68,  State( { 5.439675210757823428 } ) } );
    matlabData.insert( { 0.69,  State( { 5.499447962865401663 } ) } );
    matlabData.insert( { 0.7,   State( { 5.559681442494055679 } ) } );
    matlabData.insert( { 0.71,  State( { 5.620378256918996236 } ) } );
    matlabData.insert( { 0.72,  State( { 5.681541039488186199 } ) } );
    matlabData.insert( { 0.73,  State( { 5.743172449883068061 } ) } );
    matlabData.insert( { 0.74,  State( { 5.805275174381898741 } ) } );
    matlabData.insert( { 0.75,  State( { 5.867851926125717729 } ) } );
    matlabData.insert( { 0.76,  State( { 5.930905445386974906 } ) } );
    matlabData.insert( { 0.77,  State( { 5.994438499840844655 } ) } );
    matlabData.insert( { 0.78,  State( { 6.058453884839253101 } ) } );
    matlabData.insert( { 0.79,  State( { 6.122954423687645632 } ) } );
    matlabData.insert( { 0.8,   State( { 6.187942967924522089 } ) } );
    matlabData.insert( { 0.81,  State( { 6.25342239760376731 } ) } );
    matlabData.insert( { 0.82,  State( { 6.319395621579804983 } ) } );
    matlabData.insert( { 0.83,  State( { 6.385865577795603033 } ) } );
    matlabData.insert( { 0.84,  State( { 6.452835233573559063 } ) } );
    matlabData.insert( { 0.85,  State( { 6.520307585909294654 } ) } );
    matlabData.insert( { 0.86,  State( { 6.5882856617683876 } ) } );
    matlabData.insert( { 0.87,  State( { 6.656772518386071476 } ) } );
    matlabData.insert( { 0.88,  State( { 6.725771243569932191 } ) } );
    matlabData.insert( { 0.89,  State( { 6.795284956005631513 } ) } );
    matlabData.insert( { 0.9,   State( { 6.865316805565687828 } ) } );
    matlabData.insert( { 0.91,  State( { 6.935869973621344706 } ) } );
    matlabData.insert( { 0.92,  State( { 7.006947673357558153 } ) } );
    matlabData.insert( { 0.93,  State( { 7.078553150091133735 } ) } );
    matlabData.insert( { 0.94,  State( { 7.150689681592045072 } ) } );
    matlabData.insert( { 0.95,  State( { 7.223360578407965523 } ) } );
    matlabData.insert( { 0.96,  State( { 7.296569184192045178 } ) } );
    matlabData.insert( { 0.97,  State( { 7.37031887603396563 } ) } );
    matlabData.insert( { 0.98,  State( { 7.444613064794305286 } ) } );
    matlabData.insert( { 0.99,  State( { 7.519455195442248339 } ) } );
    matlabData.insert( { 1.0,   State( { 7.594848747396670822 } ) } );

    BurdenFaires dynamics;
    auto stateDerivativePointer = std::bind( &BurdenFaires::operator( ),
                                             &dynamics,
                                             std::placeholders::_1,
                                             std::placeholders::_2 );

    for ( const auto& pair : matlabData )
    {
       stepEuler< Real, State >( currentTime,
                                 currentState,
                                 stepSize,
                                 stateDerivativePointer );
        REQUIRE( pair.first == Approx( currentTime ).epsilon( testTolerance ).margin( testMargin ) );
        REQUIRE( pair.second[ 0 ] == Approx( currentState[ 0 ] ).epsilon( testTolerance ) );
    }
}

} // namespace tests
} // namespace integrate
