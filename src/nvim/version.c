// This is an open source non-commercial project. Dear PVS-Studio, please check
// it. PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

/// @file version.c
///
/// Nvim was forked from Vim 7.4.160.
/// Vim originated from Stevie version 3.6 (Fish disk 217) by GRWalter (Fred).

#include <inttypes.h>
#include <assert.h>
#include <limits.h>

#include "nvim/api/private/helpers.h"
#include "nvim/vim.h"
#include "nvim/ascii.h"
#include "nvim/iconv.h"
#include "nvim/version.h"
#include "nvim/charset.h"
#include "nvim/macros.h"
#include "nvim/memline.h"
#include "nvim/memory.h"
#include "nvim/message.h"
#include "nvim/screen.h"
#include "nvim/strings.h"
#include "nvim/lua/executor.h"

// version info generated by the build system
#include "auto/versiondef.h"

// for ":version", ":intro", and "nvim --version"
#ifndef NVIM_VERSION_MEDIUM
#define NVIM_VERSION_MEDIUM "v" STR(NVIM_VERSION_MAJOR)\
  "." STR(NVIM_VERSION_MINOR) "." STR(NVIM_VERSION_PATCH)\
  NVIM_VERSION_PRERELEASE
#endif
#define NVIM_VERSION_LONG "NVIM " NVIM_VERSION_MEDIUM


char *Version = VIM_VERSION_SHORT;
char *longVersion = NVIM_VERSION_LONG;
char *version_buildtype = "Build type: " NVIM_VERSION_BUILD_TYPE;
char *version_cflags = "Compilation: " NVIM_VERSION_CFLAGS;

#ifdef INCLUDE_GENERATED_DECLARATIONS
# include "version.c.generated.h"
#endif

static char *features[] = {
#ifdef HAVE_ACL
  "+acl",
#else
  "-acl",
#endif

#if (defined(HAVE_ICONV_H) && defined(USE_ICONV)) || defined(DYNAMIC_ICONV)
# ifdef DYNAMIC_ICONV
  "+iconv/dyn",
# else
  "+iconv",
# endif
#else
  "-iconv",
#endif

#ifdef HAVE_JEMALLOC
  "+jemalloc",
#else
  "-jemalloc",
#endif

#ifdef FEAT_TUI
  "+tui",
#else
  "-tui",
#endif
  NULL
};

// clang-format off
static const int included_patches[] = {
  1229,
  1230,
  // 1026,
  1025,
  1024,
  // 1023,
  // 1022,
  // 1021,
  // 1020,
  // 1019,
  // 1018,
  // 1017,
  // 1016,
  // 1015,
  // 1014,
  // 1013,
  // 1012,
  // 1011,
  // 1010,
  // 1009,
  // 1008,
  // 1007,
  // 1006,
  // 1005,
  // 1004,
  // 1003,
  // 1002,
  // 1001,
  // 1000,
  // 999,
  // 998,
  // 997,
  // 996,
  // 995,
  // 994,
  // 993,
  // 992,
  // 991,
  // 990,
  // 989,
  // 988,
  // 987,
  // 986,
  // 985,
  // 984,
  // 983,
  // 982,
  // 981,
  // 980,
  // 979,
  // 978,
  // 977,
  // 976,
  // 975,
  // 974,
  // 973,
  // 972,
  // 971,
  // 970,
  // 969,
  // 968,
  // 967,
  // 966,
  // 965,
  // 964,
  // 963,
  // 962,
  // 961,
  // 960,
  // 959,
  // 958,
  // 957,
  // 956,
  // 955,
  // 954,
  // 953,
  // 952,
  // 951,
  // 950,
  // 949,
  // 948,
  // 947,
  // 946,
  // 945,
  944,
  // 943,
  // 942,
  // 941,
  // 940,
  // 939,
  // 938,
  // 937,
  // 936,
  // 935,
  // 934,
  // 933,
  // 932,
  // 931,
  // 930,
  // 929,
  // 928,
  // 927,
  // 926,
  // 925,
  // 924,
  // 923,
  // 922,
  // 921,
  // 920,
  // 919,
  // 918,
  // 917,
  // 916,
  // 915,
  // 914,
  // 913,
  // 912,
  // 911,
  // 910,
  // 909,
  // 908,
  // 907,
  // 906,
  // 905,
  // 904,
  // 903,
  // 902,
  // 901,
  // 900,
  // 899,
  // 898,
  // 897,
  // 896,
  // 895,
  // 894,
  // 893,
  // 892,
  // 891,
  // 890,
  // 889,
  // 888,
  // 887,
  // 886,
  // 885,
  // 884,
  // 883,
  // 882,
  // 881,
  // 880,
  // 879,
  // 878,
  // 877,
  // 876,
  // 875,
  // 874,
  // 873,
  // 872,
  // 871,
  // 870,
  // 869,
  // 868,
  // 867,
  // 866,
  // 865,
  // 864,
  // 863,
  // 862,
  // 861,
  // 860,
  // 859,
  // 858,
  // 857,
  // 856,
  // 855,
  // 854,
  // 853,
  // 852,
  // 851,
  // 850,
  // 849,
  // 848,
  // 847,
  // 846,
  // 845,
  // 844,
  // 843,
  // 842,
  // 841,
  // 840,
  // 839,
  // 838,
  // 837,
  // 836,
  // 835,
  // 834,
  // 833,
  // 832,
  // 831,
  // 830,
  // 829,
  // 828,
  // 827,
  // 826,
  // 825,
  // 824,
  // 823,
  // 822,
  // 821,
  // 820,
  // 819,
  // 818,
  // 817,
  // 816,
  // 815,
  // 814,
  // 813,
  // 812,
  // 811,
  // 810,
  // 809,
  // 808,
  // 807,
  // 806,
  // 805,
  // 804,
  // 803,
  // 802,
  // 801,
  // 800,
  // 799,
  // 798,
  // 797,
  // 796,
  // 795,
  // 794,
  // 793,
  // 792,
  // 791,
  // 790,
  // 789,
  // 788,
  // 787,
  // 786,
  // 785,
  // 784,
  // 783,
  // 782,
  // 781,
  // 780,
  // 779,
  // 778,
  // 777,
  // 776,
  // 775,
  // 774,
  // 773,
  // 772,
  // 771,
  // 770,
  // 769,
  // 768,
  // 767,
  // 766,
  // 765,
  // 764,
  // 763,
  // 762,
  // 761,
  // 760,
  // 759,
  // 758,
  // 757,
  // 756,
  // 755,
  // 754,
  // 753,
  // 752,
  // 751,
  // 750,
  // 749,
  // 748,
  // 747,
  // 746,
  // 745,
  // 744,
  // 743,
  // 742,
  // 741,
  // 740,
  // 739,
  // 738,
  // 737,
  // 736,
  // 735,
  // 734,
  // 733,
  // 732,
  // 731,
  // 730,
  // 729,
  // 728,
  // 727,
  // 726,
  // 725,
  // 724,
  // 723,
  // 722,
  // 721,
  // 720,
  // 719,
  // 718,
  // 717,
  // 716,
  // 715,
  // 714,
  // 713,
  // 712,
  // 711,
  710,
  // 709,
  // 708,
  // 707,
  // 706,
  // 705,
  // 704,
  // 703,
  // 702,
  // 701,
  // 700,
  // 699,
  // 698,
  // 697,
  // 696,
  // 695,
  // 694,
  // 693,
  // 692,
  // 691,
  // 690,
  // 689,
  // 688,
  // 687,
  // 686,
  // 685,
  // 684,
  // 683,
  // 682,
  // 681,
  680,
  679,
  678,
  // 677,
  // 676,
  // 675,
  // 674,
  // 673,
  // 672,
  // 671,
  // 670,
  // 669,
  // 668,
  // 667,
  // 666,
  // 665,
  // 664,
  // 663,
  // 662,
  // 661,
  // 660,
  // 659,
  // 658,
  // 657,
  // 656,
  // 655,
  // 654,
  // 653,
  652,
  // 651,
  // 650,
  // 649,
  // 648,
  // 647,
  // 646,
  // 645,
  // 644,
  // 643,
  // 642,
  // 641,
  // 640,
  // 639,
  // 638,
  // 637,
  // 636,
  // 635,
  // 634,
  // 633,
  // 632,
  // 631,
  // 630,
  // 629,
  // 628,
  // 627,
  // 626,
  // 625,
  // 624,
  // 623,
  // 622,
  // 621,
  // 620,
  // 619,
  618,
  // 617,
  // 616,
  // 615,
  614,
  // 613,
  612,
  // 611,
  // 610,
  // 609,
  // 608,
  607,
  // 606,
  605,
  // 604,
  // 603,
  // 602,
  // 601,
  // 600,
  // 599,
  // 598,
  // 597,
  // 596,
  // 595,
  // 594,
  // 593,
  // 592,
  // 591,
  // 590,
  // 589,
  // 588,
  // 587,
  // 586,
  // 585,
  // 584,
  // 583,
  // 582,
  // 581,
  // 580,
  // 579,
  // 578,
  // 577,
  // 576,
  // 575,
  // 574,
  // 573,
  // 572,
  571,
  // 570,
  // 569,
  // 568,
  // 567,
  // 566,
  // 565,
  // 564,
  // 563,
  // 562,
  561,
  // 560,
  // 559,
  // 558,
  // 557,
  // 556,
  555,
  554,
  553,
  552,
  // 551,
  550,
  // 549,
  // 548,
  // 547,
  // 546,
  // 545,
  // 544,
  // 543,
  // 542,
  // 541,
  // 540,
  // 539,
  // 538,
  // 537,
  // 536,
  // 535,
  // 534,
  // 533,
  // 532,
  // 531,
  // 530,
  // 529,
  // 528,
  // 527,
  // 526,
  // 525,
  524,
  // 523,
  // 522,
  // 521,
  // 520,
  // 519,
  518,
  // 517,
  // 516,
  // 515,
  // 514,
  // 513,
  // 512,
  // 511,
  // 510,
  // 509,
  // 508,
  // 507,
  // 506,
  // 505,
  // 504,
  // 503,
  502,
  // 501,
  // 500,
  499,
  498,
  // 497,
  // 496,
  // 495,
  // 494,
  // 493,
  // 492,
  // 491,
  // 490,
  // 489,
  // 488,
  487,
  486,
  485,
  // 484,
  483,
  482,
  // 481,
  // 480,
  // 479,
  478,
  477,
  // 476,
  // 475,
  // 474,
  // 473,
  // 472,
  // 471,
  // 470,
  // 469,
  // 468,
  // 467,
  // 466,
  465,
  // 464,
  // 463,
  // 462,
  461,
  // 460,
  459,
  // 458,
  457,
  // 456,
  // 455,
  // 454,
  453,
  // 452,
  // 451,
  // 450,
  // 449,
  // 448,
  // 447,
  // 446,
  // 445,
  // 444,
  // 443,
  // 442,
  // 441,
  // 440,
  // 439,
  // 438,
  437,
  // 436,
  // 435,
  // 434,
  // 433,
  // 432,
  // 431,
  // 430,
  // 429,
  // 428,
  // 427,
  // 426,
  // 425,
  // 424,
  // 423,
  // 422,
  // 421,
  // 420,
  // 419,
  // 418,
  // 417,
  // 416,
  // 415,
  // 414,
  // 413,
  // 412,
  // 411,
  // 410,
  // 409,
  408,
  407,
  // 406,
  // 405 NA
  // 404,
  // 403,
  // 402,
  // 401,
  // 400 NA
  // 399,
  // 398,
  // 397,
  // 396,
  // 395,
  394,
  393,
  // 392,
  // 391,
  390,
  // 389,
  388,
  // 387,
  // 386,
  // 385,
  // 384,
  // 383,
  // 382,
  // 381,
  // 380,
  // 379,
  378,
  377,
  376,
  // 375,
  // 374,
  // 373,
  // 372,
  // 371,
  // 370,
  // 369,
  // 368,
  // 367,
  // 366,
  // 365,
  // 364,
  // 363,
  // 362,
  // 361,
  360,
  // 359,
  // 358,
  // 357,
  // 356,
  // 355,
  // 354,
  353,
  // 352,
  // 351,
  // 350,
  // 349,
  // 348,
  347,
  // 346,
  345,
  // 344,
  343,
  // 342,
  341,
  // 340,
  // 339,
  // 338,
  // 337,
  // 336,
  // 335,
  // 334,
  333,
  // 332,
  331,
  330,
  // 329,
  328,
  327,
  326,
  325,
  324,
  // 323,
  322,
  // 321,
  // 320,
  319,
  // 318,
  // 317,
  // 316,
  // 315,
  // 314,
  // 313,
  // 312,
  311,
  // 310,
  // 309,
  308,
  307,
  // 306,
  305,
  // 304,
  // 303,
  // 302, NA
  // 301,
  300,
  // 299,
  // 298,
  297,
  // 296,
  // 295,
  294,
  // 293,
  // 292,
  291,
  290,
  // 289,
  // 288 NA
  // 287,
  // 286,
  // 285 NA
  // 284 NA
  // 283,
  282,
  // 281 NA
  280,
  // 279 NA
  // 278 NA
  // 277 NA
  // 276 NA
  275,
  274,
  // 273 NA
  // 272 NA
  // 271 NA
  // 270 NA
  // 269 NA
  // 268 NA
  // 267 NA
  266,
  // 265,
  // 264,
  // 263,
  // 262,
  // 261,
  // 260 NA
  259,
  258,
  // 257 NA
  // 256,
  // 255,
  // 254,
  253,
  // 252,
  // 251,
  250,
  // 249 NA
  // 248,
  247,
  // 246 NA
  // 245,
  // 244,
  243,
  // 242,
  // 241 NA
  // 240 NA
  // 239 NA
  // 238,
  // 237,
  // 236,
  235,
  // 234,
  // 233,
  // 232 NA
  // 231,
  // 230,
  229,
  // 228,
  // 227,
  // 226,
  // 225,
  // 224,
  223,
  // 222,
  // 221 NA
  // 220,
  219,
  // 218,
  // 217 NA
  // 216,
  // 215,
  // 214,
  // 213 NA
  // 212,
  // 211 NA
  // 210,
  209,
  208,
  // 207,
  206,
  205,
  // 204,
  // 203 NA
  // 202,
  // 201,
  // 200,
  // 199 NA
  // 198,
  // 197,
  196,
  195,
  194,
  // 193 NA
  // 192 NA
  // 191 NA
  190,
  189,
  188,
  // 187 NA
  186,
  // 185,
  // 184,
  // 183 NA
  182,
  181,
  // 180,
  179,
  178,
  177,
  176,
  // 175,
  174,
  // 173 NA
  172,
  // 171,
  // 170,
  // 169,
  168,
  167,
  // 166,
  165,
  164,
  // 163 NA
  // 162 NA
  // 161 NA
  // 160,
  159,
  158,
  157,
  156,
  155,
  // 154,
  // 153,
  // 152 NA
  // 151,
  150,
  149,
  148,
  147,
  146,
  // 145 NA
  // 144 NA
  143,
  142,
  // 141,
  140,
  // 139 NA
  // 138 NA
  137,
  136,
  135,
  134,
  133,
  132,
  131,
  // 130 NA
  // 129 NA
  128,
  127,
  126,
  125,
  124,
  // 123 NA
  // 122 NA
  121,
  // 120 NA
  119,
  118,
  // 117 NA
  116,
  // 115 NA
  // 114 NA
  // 113 NA
  112,
  111,
  110,
  // 109 NA
  // 108 NA
  // 107 NA
  106,
  // 105 NA
  104,
  // 103 NA
  102,
  101,
  100,
  99,
  // 98 NA
  // 97 NA
  // 96,
  // 95 NA
  // 94 NA
  // 93 NA
  92,
  91,
  90,
  // 89 NA
  88,
  // 87 NA
  86,
  85,
  84,
  83,
  // 82 NA
  81,
  // 80 NA
  79,
  78,
  // 77 NA
  // 76 NA
  75,
  // 74,
  73,
  // 72 NA
  // 71 NA
  // 70 NA
  69,
  68,
  // 67 NA
  66,
  // 65 NA
  64,
  // 63 NA
  62,
  // 61 NA
  60,
  // 59 NA
  58,
  57,
  56,
  // 55 NA
  // 54 NA
  53,
  52,
  // 51 NA
  // 50 NA
  49,
  // 48 NA
  47,
  46,
  // 45 NA
  44,
  43,
  42,
  41,
  40,
  // 39 NA
  38,
  37,
  // 36 NA
  35,
  34,
  33,
  32,
  31,
  // 30 NA
  // 29 NA
  // 28 NA
  // 27 NA
  26,
  25,
  // 24 NA
  23,
  // 22 NA
  // 21,
  20,
  19,
  // 18,
  17,
  // 16 NA
  // 15 NA
  // 14 NA
  // 13 NA
  12,
  // 11 NA
  // 10 NA
  // 9 NA
  8,
  // 7 NA
  6,
  // 5 NA
  4,
  3,
  2,
  1,
  0
};
// clang-format on

/// Compares a version string to the current Nvim version.
///
/// @param version Version string like "1.3.42"
///
/// @return true if Nvim is at or above the version.
bool has_nvim_version(const char *const version_str)
  FUNC_ATTR_PURE FUNC_ATTR_WARN_UNUSED_RESULT FUNC_ATTR_NONNULL_ALL
{
  const char *p = version_str;
  int major = 0;
  int minor = 0;
  int patch = 0;

  if (!ascii_isdigit(*p)) {
    return false;
  }
  major = atoi(p);
  p = strchr(p, '.');  // Find the next dot.

  if (p) {
    p++;  // Advance past the dot.
    if (!ascii_isdigit(*p)) {
      return false;
    }
    minor = atoi(p);
    p = strchr(p, '.');
    if (p) {
      p++;
      if (!ascii_isdigit(*p)) {
        return false;
      }
      patch = atoi(p);
    }
  }

  return (major < NVIM_VERSION_MAJOR
          || (major == NVIM_VERSION_MAJOR
              && (minor < NVIM_VERSION_MINOR
                  || (minor == NVIM_VERSION_MINOR
                      && patch <= NVIM_VERSION_PATCH))));
}

/// Checks whether a Vim patch has been included.
///
/// @param n Patch number.
///
/// @return true if patch `n` has been included.
bool has_vim_patch(int n)
{
  for (int i = 0; included_patches[i] != 0; i++) {
    if (included_patches[i] == n) {
      return true;
    }
  }
  return false;
}

Dictionary version_dict(void) {
  Dictionary d = ARRAY_DICT_INIT;
  PUT(d, "major", INTEGER_OBJ(NVIM_VERSION_MAJOR));
  PUT(d, "minor", INTEGER_OBJ(NVIM_VERSION_MINOR));
  PUT(d, "patch", INTEGER_OBJ(NVIM_VERSION_PATCH));
  PUT(d, "api_level", INTEGER_OBJ(NVIM_API_LEVEL));
  PUT(d, "api_compatible", INTEGER_OBJ(NVIM_API_LEVEL_COMPAT));
  PUT(d, "api_prerelease", BOOLEAN_OBJ(NVIM_API_PRERELEASE));
  return d;
}

void ex_version(exarg_T *eap)
{
  // Ignore a ":version 9.99" command.
  if (*eap->arg == NUL) {
    msg_putchar('\n');
    list_version();
  }
}

/// List all features aligned in columns, dictionary style.
static void list_features(void)
{
  int nfeat = 0;
  int width = 0;

  // Find the length of the longest feature name, use that + 1 as the column
  // width
  int i;
  for (i = 0; features[i] != NULL; ++i) {
    int l = (int)STRLEN(features[i]);

    if (l > width) {
      width = l;
    }
    nfeat++;
  }
  width += 1;

  if (Columns < width) {
    // Not enough screen columns - show one per line
    for (i = 0; features[i] != NULL; ++i) {
      version_msg(features[i]);
      if (msg_col > 0) {
        msg_putchar('\n');
      }
    }
    return;
  }

  // The rightmost column doesn't need a separator.
  // Sacrifice it to fit in one more column if possible.
  int ncol = (int)(Columns + 1) / width;
  int nrow = nfeat / ncol + (nfeat % ncol ? 1 : 0);

  // i counts columns then rows.  idx counts rows then columns.
  for (i = 0; !got_int && i < nrow * ncol; ++i) {
    int idx = (i / ncol) + (i % ncol) * nrow;
    if (idx < nfeat) {
      int last_col = (i + 1) % ncol == 0;
      msg_puts(features[idx]);
      if (last_col) {
        if (msg_col > 0) {
          msg_putchar('\n');
        }
      } else {
        msg_putchar(' ');
      }
    } else {
      if (msg_col > 0) {
        msg_putchar('\n');
      }
    }
  }
  MSG_PUTS("See \":help feature-compile\"\n\n");
}

void list_lua_version(void)
{
  typval_T luaver_tv;
  typval_T arg = { .v_type = VAR_UNKNOWN };  // No args.
  char *luaver_expr = "((jit and jit.version) and jit.version or _VERSION)";
  executor_eval_lua(cstr_as_string(luaver_expr), &arg, &luaver_tv);
  assert(luaver_tv.v_type == VAR_STRING);
  MSG(luaver_tv.vval.v_string);
  xfree(luaver_tv.vval.v_string);
}

void list_version(void)
{
  MSG(longVersion);
  MSG(version_buildtype);
  list_lua_version();
  MSG(version_cflags);

#ifdef HAVE_PATHDEF

  if ((*compiled_user != NUL) || (*compiled_sys != NUL)) {
    MSG_PUTS(_("\nCompiled "));

    if (*compiled_user != NUL) {
      MSG_PUTS(_("by "));
      MSG_PUTS(compiled_user);
    }

    if (*compiled_sys != NUL) {
      MSG_PUTS("@");
      MSG_PUTS(compiled_sys);
    }
  }
#endif  // ifdef HAVE_PATHDEF

  version_msg(_("\n\nFeatures: "));

  list_features();

#ifdef SYS_VIMRC_FILE
  version_msg(_("   system vimrc file: \""));
  version_msg(SYS_VIMRC_FILE);
  version_msg("\"\n");
#endif  // ifdef SYS_VIMRC_FILE
#ifdef HAVE_PATHDEF

  if (*default_vim_dir != NUL) {
    version_msg(_("  fall-back for $VIM: \""));
    version_msg(default_vim_dir);
    version_msg("\"\n");
  }

  if (*default_vimruntime_dir != NUL) {
    version_msg(_(" f-b for $VIMRUNTIME: \""));
    version_msg(default_vimruntime_dir);
    version_msg("\"\n");
  }
#endif  // ifdef HAVE_PATHDEF

  version_msg("\nRun :checkhealth for more info");
}

/// Output a string for the version message.  If it's going to wrap, output a
/// newline, unless the message is too long to fit on the screen anyway.
///
/// @param s
static void version_msg(char *s)
{
  int len = (int)STRLEN(s);

  if (!got_int
      && (len < (int)Columns)
      && (msg_col + len >= (int)Columns)
      && (*s != '\n')) {
    msg_putchar('\n');
  }

  if (!got_int) {
    MSG_PUTS(s);
  }
}


/// Show the intro message when not editing a file.
void maybe_intro_message(void)
{
  if (bufempty()
      && (curbuf->b_fname == NULL)
      && (firstwin->w_next == NULL)
      && (vim_strchr(p_shm, SHM_INTRO) == NULL)) {
    intro_message(FALSE);
  }
}

/// Give an introductory message about Vim.
/// Only used when starting Vim on an empty file, without a file name.
/// Or with the ":intro" command (for Sven :-).
///
/// @param colon TRUE for ":intro"
void intro_message(int colon)
{
  int i;
  long row;
  long blanklines;
  int sponsor;
  char *p;
  static char *(lines[]) = {
    N_(NVIM_VERSION_LONG),
    "",
    N_("Nvim is open source and freely distributable"),
    N_("https://neovim.io/community"),
    "",
    N_("type  :help nvim<Enter>       if you are new! "),
    N_("type  :checkhealth<Enter>     to optimize Nvim"),
    N_("type  :q<Enter>               to exit         "),
    N_("type  :help<Enter>            for help        "),
    "",
    N_("Help poor children in Uganda!"),
    N_("type  :help iccf<Enter>       for information "),
  };

  // blanklines = screen height - # message lines
  size_t lines_size = ARRAY_SIZE(lines);
  assert(lines_size <= LONG_MAX);

  blanklines = Rows - ((long)lines_size - 1l);

  // Don't overwrite a statusline.  Depends on 'cmdheight'.
  if (p_ls > 1) {
    blanklines -= Rows - topframe->fr_height;
  }

  if (blanklines < 0) {
    blanklines = 0;
  }

  // Show the sponsor and register message one out of four times, the Uganda
  // message two out of four times.
  sponsor = (int)time(NULL);
  sponsor = ((sponsor & 2) == 0) - ((sponsor & 4) == 0);

  // start displaying the message lines after half of the blank lines
  row = blanklines / 2;

  if (((row >= 2) && (Columns >= 50)) || colon) {
    for (i = 0; i < (int)ARRAY_SIZE(lines); ++i) {
      p = lines[i];

      if (sponsor != 0) {
        if (strstr(p, "children") != NULL) {
          p = sponsor < 0
              ? N_("Sponsor Vim development!")
              : N_("Become a registered Vim user!");
        } else if (strstr(p, "iccf") != NULL) {
          p = sponsor < 0
              ? N_("type  :help sponsor<Enter>    for information ")
              : N_("type  :help register<Enter>   for information ");
        } else if (strstr(p, "Orphans") != NULL) {
          p = N_("menu  Help->Sponsor/Register  for information    ");
        }
      }

      if (*p != NUL) {
        do_intro_line(row, (char_u *)_(p), 0);
      }
      row++;
    }
  }

  // Make the wait-return message appear just below the text.
  if (colon) {
    assert(row <= INT_MAX);
    msg_row = (int)row;
  }
}

static void do_intro_line(long row, char_u *mesg, int attr)
{
  long col;
  char_u *p;
  int l;
  int clen;

  // Center the message horizontally.
  col = vim_strsize(mesg);

  col = (Columns - col) / 2;

  if (col < 0) {
    col = 0;
  }

  // Split up in parts to highlight <> items differently.
  for (p = mesg; *p != NUL; p += l) {
    clen = 0;

    for (l = 0; p[l] != NUL
         && (l == 0 || (p[l] != '<' && p[l - 1] != '>')); ++l) {
      if (has_mbyte) {
        clen += ptr2cells(p + l);
        l += (*mb_ptr2len)(p + l) - 1;
      } else {
        clen += byte2cells(p[l]);
      }
    }
    assert(row <= INT_MAX && col <= INT_MAX);
    screen_puts_len(p, l, (int)row, (int)col, *p == '<' ? hl_attr(HLF_8) : attr);
    col += clen;
  }
}

/// ":intro": clear screen, display intro screen and wait for return.
///
/// @param eap
void ex_intro(exarg_T *eap)
{
  screenclear();
  intro_message(TRUE);
  wait_return(TRUE);
}

