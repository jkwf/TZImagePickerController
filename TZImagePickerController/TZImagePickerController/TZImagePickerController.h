//
//  TZImagePickerController.h
//  TZImagePickerController
//
//  Created by 谭真 on 15/12/24.
//  Copyright © 2015年 谭真. All rights reserved.
//  version 2.0.1 - 2018.03.25
//  更多信息，请前往项目的github地址：https://github.com/banchichen/TZImagePickerController

/*
 经过测试，比起xib的方式，把TZAssetCell改用纯代码的方式来写，滑动帧数明显提高了（约提高10帧左右）
 
 最初发现这个问题并修复的是@小鱼周凌宇同学，她的博客地址: http://zhoulingyu.com/
 表示感谢~
 
 原来xib确实会导致性能问题啊...大家也要注意了...
 */

#import <UIKit/UIKit.h>
#import "TZAssetModel.h"
#import "NSBundle+TZImagePicker.h"

#define iOS7Later ([UIDevice currentDevice].systemVersion.floatValue >= 7.0f)
#define iOS8Later ([UIDevice currentDevice].systemVersion.floatValue >= 8.0f)
#define iOS9Later ([UIDevice currentDevice].systemVersion.floatValue >= 9.0f)
#define iOS9_1Later ([UIDevice currentDevice].systemVersion.floatValue >= 9.1f)

@protocol TZImagePickerControllerDelegate;
@interface TZImagePickerController : UINavigationController

#pragma mark -
/// Use this init method / 用这个初始化方法
- (instancetype)initWithMaxImagesCount:(NSInteger)maxImagesCount delegate:(id<TZImagePickerControllerDelegate>)delegate;
- (instancetype)initWithMaxImagesCount:(NSInteger)maxImagesCount columnNumber:(NSInteger)columnNumber delegate:(id<TZImagePickerControllerDelegate>)delegate;
- (instancetype)initWithMaxImagesCount:(NSInteger)maxImagesCount columnNumber:(NSInteger)columnNumber delegate:(id<TZImagePickerControllerDelegate>)delegate pushPhotoPickerVc:(BOOL)pushPhotoPickerVc;
/// This init method just for previewing photos / 用这个初始化方法以预览图片
- (instancetype)initWithSelectedAssets:(NSMutableArray *)selectedAssets selectedPhotos:(NSMutableArray *)selectedPhotos index:(NSInteger)index;
/// This init method for crop photo / 用这个初始化方法以裁剪图片
- (instancetype)initCropTypeWithAsset:(id)asset photo:(UIImage *)photo completion:(void (^)(UIImage *cropImage,id asset))completion;

// MARK: - TS 定制初始化方法
/// TS_需要裁TS裁剪的初始化方法
/// 可以初始化之后进行修改，比如标题，裁剪区域样式
- (instancetype)initWithMaxImagesCountTSType:(NSInteger)maxImagesCount columnNumber:(NSInteger)columnNumber delegate:(id<TZImagePickerControllerDelegate>)delegate pushPhotoPickerVc:(BOOL)pushPhotoPickerVc square:(BOOL)square shouldPick:(BOOL)shouldPick topTitle:(NSString *)topTitle;
/// TS_外部可以改变主题色的TS裁剪初始化方法
/// 除主题色都可以初始化之后进行修改，比如标题，裁剪区域样式
- (instancetype)initWithMaxImagesCountTSType:(NSInteger)maxImagesCount columnNumber:(NSInteger)columnNumber delegate:(id<TZImagePickerControllerDelegate>)delegate pushPhotoPickerVc:(BOOL)pushPhotoPickerVc square:(BOOL)square shouldPick:(BOOL)shouldPick topTitle:(NSString *)topTitle mainColor:(UIColor *)mainColor;
/// TS_外部可以改变主题色，快捷初始化方法（默认进入照片列表）
- (instancetype)initWithMaxImagesCount:(NSInteger)maxImagesCount delegate:(id<TZImagePickerControllerDelegate>)delegate mainColor:(UIColor *)mainColor;
/// TS_外部可以改变主题色，设置列数初始化方法（默认进入照片列表）
- (instancetype)initWithMaxImagesCount:(NSInteger)maxImagesCount columnNumber:(NSInteger)columnNumber delegate:(id<TZImagePickerControllerDelegate>)delegate mainColor:(UIColor *)mainColor;
/// TS_外部可以改变主题色，设置列数，是否直接进入照片列表初始化方法
- (instancetype)initWithMaxImagesCount:(NSInteger)maxImagesCount columnNumber:(NSInteger)columnNumber delegate:(id<TZImagePickerControllerDelegate>)delegate pushPhotoPickerVc:(BOOL)pushPhotoPickerVc mainColor:(UIColor *)mainColor;
// MARK: - end

/// This init method just for previewing photos / 用这个初始化方法以预览图片
- (instancetype)initWithSelectedAssets:(NSMutableArray *)selectedAssets selectedPhotos:(NSMutableArray *)selectedPhotos index:(NSInteger)index mainColor:(UIColor *)mainColor;
/// This init method for crop photo / 用这个初始化方法以裁剪图片
- (instancetype)initCropTypeWithAsset:(id)asset photo:(UIImage *)photo completion:(void (^)(UIImage *cropImage,id asset))completion mainColor:(UIColor *)mainColor;

#pragma mark -
/// Default is 9 / 默认最大可选9张图片
@property (nonatomic, assign) NSInteger maxImagesCount;

/// The minimum count photos user must pick, Default is 0
/// 最小照片必选张数,默认是0
@property (nonatomic, assign) NSInteger minImagesCount;

/// Always enale the done button, not require minimum 1 photo be picked
/// 让完成按钮一直可以点击，无须最少选择一张图片
@property (nonatomic, assign) BOOL alwaysEnableDoneBtn;

/// Sort photos ascending by modificationDate，Default is YES
/// 对照片排序，按修改时间升序，默认是YES。如果设置为NO,最新的照片会显示在最前面，内部的拍照按钮会排在第一个
@property (nonatomic, assign) BOOL sortAscendingByModificationDate;

/// The pixel width of output image, Default is 828px / 导出图片的宽度，默认828像素宽
@property (nonatomic, assign) CGFloat photoWidth;

/// Default is 600px / 默认600像素宽
@property (nonatomic, assign) CGFloat photoPreviewMaxWidth;

/// Default is 15, While fetching photo, HUD will dismiss automatic if timeout;
/// 超时时间，默认为15秒，当取图片时间超过15秒还没有取成功时，会自动dismiss HUD；
@property (nonatomic, assign) NSInteger timeout;

/// Default is YES, if set NO, the original photo button will hide. user can't picking original photo.
/// 默认为YES，如果设置为NO,原图按钮将隐藏，用户不能选择发送原图
@property (nonatomic, assign) BOOL allowPickingOriginalPhoto;

/// Default is YES, if set NO, user can't picking video.
/// 默认为YES，如果设置为NO,用户将不能选择视频
@property (nonatomic, assign) BOOL allowPickingVideo;
/// Default is NO / 默认为NO，为YES时可以多选视频/gif图片，和照片共享最大可选张数maxImagesCount的限制
@property (nonatomic, assign) BOOL allowPickingMultipleVideo;

/// Default is NO, if set YES, user can picking gif image.
/// 默认为NO，如果设置为YES,用户可以选择gif图片
@property (nonatomic, assign) BOOL allowPickingGif;

/// Default is YES, if set NO, user can't picking image.
/// 默认为YES，如果设置为NO,用户将不能选择发送图片
@property(nonatomic, assign) BOOL allowPickingImage;

/// Default is YES, if set NO, user can't take picture.
/// 默认为YES，如果设置为NO,拍照按钮将隐藏,用户将不能选择照片
@property(nonatomic, assign) BOOL allowTakePicture;

/// 首选语言，如果设置了就用该语言，不设则取当前系统语言。
/// 由于目前只支持中文、繁体中文、英文、越南语。故该属性只支持zh-Hans、zh-Hant、en、vi四种值，其余值无效。
@property (copy, nonatomic) NSString *preferredLanguage;

/// 语言bundle，preferredLanguage变化时languageBundle会变化
/// 可通过手动设置bundle，让选择器支持新的的语言（需要在设置preferredLanguage后设置languageBundle）。欢迎提交PR把语言文件提交上来~
@property (strong, nonatomic) NSBundle *languageBundle;

/// Default is YES, if set NO, user can't preview photo.
/// 默认为YES，如果设置为NO,预览按钮将隐藏,用户将不能去预览照片
@property (nonatomic, assign) BOOL allowPreview;

/// Default is YES, if set NO, the picker don't dismiss itself.
/// 默认为YES，如果设置为NO, 选择器将不会自己dismiss
@property(nonatomic, assign) BOOL autoDismiss;

/// Default is YES, if set NO, in the delegate method the photos and infos will be nil, only assets hava value.
/// 默认为NO，如果设置为YES，代理方法里photos和infos会是nil，只返回assets
@property (assign, nonatomic) BOOL onlyReturnAsset;

/// The photos user have selected
/// 用户选中过的图片数组
@property (nonatomic, strong) NSMutableArray *selectedAssets;
@property (nonatomic, strong) NSMutableArray<TZAssetModel *> *selectedModels;

/// Minimum selectable photo width, Default is 0
/// 最小可选中的图片宽度，默认是0，小于这个宽度的图片不可选中
@property (nonatomic, assign) NSInteger minPhotoWidthSelectable;
@property (nonatomic, assign) NSInteger minPhotoHeightSelectable;
/// Hide the photo what can not be selected, Default is NO
/// 隐藏不可以选中的图片，默认是NO，不推荐将其设置为YES
@property (nonatomic, assign) BOOL hideWhenCanNotSelect;
/// Deprecated, Use statusBarStyle (顶部statusBar 是否为系统默认的黑色，默认为NO)
@property (nonatomic, assign) BOOL isStatusBarDefault __attribute__((deprecated("Use -statusBarStyle.")));
/// statusBar的样式，默认为UIStatusBarStyleLightContent
@property (assign, nonatomic) UIStatusBarStyle statusBarStyle;

#pragma mark -
/// Single selection mode, valid when maxImagesCount = 1
/// 单选模式,maxImagesCount为1时才生效
@property (nonatomic, assign) BOOL showSelectBtn;        ///< 在单选模式下，照片列表页中，显示选择按钮,默认为NO
@property (nonatomic, assign) BOOL allowCrop;            ///< 允许裁剪,默认为YES，showSelectBtn为NO才生效
@property (nonatomic, assign) CGRect cropRect;           ///< 裁剪框的尺寸
@property (nonatomic, assign) CGRect cropRectPortrait;   ///< 裁剪框的尺寸(竖屏)
@property (nonatomic, assign) CGRect cropRectLandscape;  ///< 裁剪框的尺寸(横屏)
@property (nonatomic, assign) BOOL needCircleCrop;       ///< 需要圆形裁剪框
@property (nonatomic, assign) NSInteger circleCropRadius;  ///< 圆形裁剪框半径大小
@property (nonatomic, copy) void (^cropViewSettingBlock)(UIView *cropView);     ///< 自定义裁剪框的其他属性

@property (nonatomic, copy) void (^navLeftBarButtonSettingBlock)(UIButton *leftButton);     ///< 自定义返回按钮样式及其属性

#pragma mark -
- (id)showAlertWithTitle:(NSString *)title;
- (void)hideAlertView:(id)alertView;
- (void)showProgressHUD;
- (void)hideProgressHUD;
@property (nonatomic, assign) BOOL isSelectOriginalPhoto;
@property (assign, nonatomic) BOOL needShowStatusBar;

#pragma mark -
@property (nonatomic, copy) NSString *takePictureImageName;
/// 列表 勾选图标
@property (nonatomic, copy) NSString *photoSelImageName;
@property (nonatomic, copy) NSString *photoDefImageName;
/// 预览页 勾选图标
@property (nonatomic, copy) NSString *photoPreviewSelImageName;
@property (nonatomic, copy) NSString *photoPreviewDefImageName;

@property (nonatomic, copy) NSString *photoOriginSelImageName;
@property (nonatomic, copy) NSString *photoOriginDefImageName;
@property (nonatomic, copy) NSString *photoPreviewOriginDefImageName;
@property (nonatomic, copy) NSString *photoNumberIconImageName;

#pragma mark -
/// Appearance / 外观颜色 + 按钮文字
@property (nonatomic, strong) UIColor *oKButtonTitleColorNormal;
@property (nonatomic, strong) UIColor *oKButtonTitleColorDisabled;
// 确定按钮的背景颜色
@property (nonatomic, strong) UIColor *oKButtonBackGroundColorEnabled;
@property (nonatomic, strong) UIColor *oKButtonBackGroundColorDisabled;
@property (nonatomic, strong) UIColor *naviBgColor;
@property (nonatomic, strong) UIColor *naviTitleColor;
@property (nonatomic, strong) UIFont *naviTitleFont;
@property (nonatomic, strong) UIColor *barItemTextColor;
@property (nonatomic, strong) UIFont *barItemTextFont;

@property (nonatomic, copy) NSString *doneBtnTitleStr;
@property (nonatomic, copy) NSString *cancelBtnTitleStr;
@property (nonatomic, copy) NSString *previewBtnTitleStr;
@property (nonatomic, copy) NSString *fullImageBtnTitleStr;
@property (nonatomic, copy) NSString *settingBtnTitleStr;
@property (nonatomic, copy) NSString *processHintStr;
// MARK: - TS 定制属性
///是正方形还是长方形
@property (assign, nonatomic) BOOL isSquare;
///是否需要裁剪
@property (assign, nonatomic) BOOL shouldPick;
///顶部title标题
@property (nonatomic, copy) NSString *topTitle;
/// 整个项目主题色
@property (nonatomic, copy) UIColor *mainColor;
/// 相册图片选中按钮图片
@property (nonatomic, copy) UIImage *selectImage;
/// 相册图片预览页面选中按钮 选中图片
@property (nonatomic, copy) UIImage *previewSelectBtnSelImage;
/// 相册图片预览页面选中按钮 未选中图片
@property (nonatomic, copy) UIImage *previewSelectBtnDefImage;
/// 整个项目的返回按钮图片
@property(nonatomic,strong)UIImage *backImage;
/// 裁剪页面返回按钮图片
@property(nonatomic,strong)UIImage *videoEditVCbackImage;
/// 相册图片拍摄视频图片
@property (nonatomic, copy) UIImage *takeVideo;
/// 视频编辑页面左图片
@property (nonatomic, copy) UIImage *editFaceLeft;
/// 视频编辑页面右图片
@property (nonatomic, copy) UIImage *editFaceRight;
/// 整个项目的视频封面选择框
@property(nonatomic,strong)UIImage *picCoverImage;
/// (视频)是否需要选择封面,默认为YES
/// 不选择则默认第一帧
@property(nonatomic, assign) BOOL shouldSetCoverImage;

// MARK: end

#pragma mark -
- (void)cancelButtonClick;

// The picker should dismiss itself; when it dismissed these handle will be called.
// You can also set autoDismiss to NO, then the picker don't dismiss itself.
// If isOriginalPhoto is YES, user picked the original photo.
// You can get original photo with asset, by the method [[TZImageManager manager] getOriginalPhotoWithAsset:completion:].
// The UIImage Object in photos default width is 828px, you can set it by photoWidth property.
// 这个照片选择器会自己dismiss，当选择器dismiss的时候，会执行下面的handle
// 你也可以设置autoDismiss属性为NO，选择器就不会自己dismis了
// 如果isSelectOriginalPhoto为YES，表明用户选择了原图
// 你可以通过一个asset获得原图，通过这个方法：[[TZImageManager manager] getOriginalPhotoWithAsset:completion:]
// photos数组里的UIImage对象，默认是828像素宽，你可以通过设置photoWidth属性的值来改变它
@property (nonatomic, copy) void (^didFinishPickingPhotosHandle)(NSArray<UIImage *> *photos,NSArray *assets,BOOL isSelectOriginalPhoto);
@property (nonatomic, copy) void (^didFinishPickingPhotosWithInfosHandle)(NSArray<UIImage *> *photos,NSArray *assets,BOOL isSelectOriginalPhoto,NSArray<NSDictionary *> *infos);
@property (nonatomic, copy) void (^imagePickerControllerDidCancelHandle)(void);

// If user picking a video, this handle will be called.
// If system version > iOS8,asset is kind of PHAsset class, else is ALAsset class.
// 如果用户选择了一个视频，下面的handle会被执行
// 如果系统版本大于iOS8，asset是PHAsset类的对象，否则是ALAsset类的对象
@property (nonatomic, copy) void (^didFinishPickingVideoHandle)(UIImage *coverImage,id asset);

// If user picking a gif image, this callback will be called.
// 如果用户选择了一个gif图片，下面的handle会被执行
@property (nonatomic, copy) void (^didFinishPickingGifImageHandle)(UIImage *animatedImage,id sourceAssets);

@property (nonatomic, weak) id<TZImagePickerControllerDelegate> pickerDelegate;

@end


@protocol TZImagePickerControllerDelegate <NSObject>
@optional
// The picker should dismiss itself; when it dismissed these handle will be called.
// You can also set autoDismiss to NO, then the picker don't dismiss itself.
// If isOriginalPhoto is YES, user picked the original photo.
// You can get original photo with asset, by the method [[TZImageManager manager] getOriginalPhotoWithAsset:completion:].
// The UIImage Object in photos default width is 828px, you can set it by photoWidth property.
// 这个照片选择器会自己dismiss，当选择器dismiss的时候，会执行下面的handle
// 你也可以设置autoDismiss属性为NO，选择器就不会自己dismis了
// 如果isSelectOriginalPhoto为YES，表明用户选择了原图
// 你可以通过一个asset获得原图，通过这个方法：[[TZImageManager manager] getOriginalPhotoWithAsset:completion:]
// photos数组里的UIImage对象，默认是828像素宽，你可以通过设置photoWidth属性的值来改变它
- (void)imagePickerController:(TZImagePickerController *)picker didFinishPickingPhotos:(NSArray<UIImage *> *)photos sourceAssets:(NSArray *)assets isSelectOriginalPhoto:(BOOL)isSelectOriginalPhoto;
- (void)imagePickerController:(TZImagePickerController *)picker didFinishPickingPhotos:(NSArray<UIImage *> *)photos sourceAssets:(NSArray *)assets isSelectOriginalPhoto:(BOOL)isSelectOriginalPhoto infos:(NSArray<NSDictionary *> *)infos;
//- (void)imagePickerControllerDidCancel:(TZImagePickerController *)picker __attribute__((deprecated("Use -tz_imagePickerControllerDidCancel:.")));
- (void)tz_imagePickerControllerDidCancel:(TZImagePickerController *)picker;

// If user picking a video, this callback will be called.
// If system version > iOS8,asset is kind of PHAsset class, else is ALAsset class.
// 如果用户选择了一个视频，下面的handle会被执行
// 如果系统版本大于iOS8，asset是PHAsset类的对象，否则是ALAsset类的对象
- (void)imagePickerController:(TZImagePickerController *)picker didFinishPickingVideo:(UIImage *)coverImage sourceAssets:(id)asset;
// TS定制
- (void)imagePickerController:(TZImagePickerController *)picker didFinishEditVideoCoverImage:(UIImage *)coverImage videoURL:(id)videoURL;
// If user picking a gif image, this callback will be called.
// 如果用户选择了一个gif图片，下面的handle会被执行
- (void)imagePickerController:(TZImagePickerController *)picker didFinishPickingGifImage:(UIImage *)animatedImage sourceAssets:(id)asset;

// Decide album show or not't
// 决定相册显示与否 albumName:相册名字 result:相册原始数据
- (BOOL)isAlbumCanSelect:(NSString *)albumName result:(id)result;

// Decide asset show or not't
// 决定照片显示与否
- (BOOL)isAssetCanSelect:(id)asset;

// 点击了拍照相册内的拍照按钮
- (void)imagePickerControllerDidClickTakePhotoBtn:(TZImagePickerController *)picker;
@end


@interface TZAlbumPickerController : UIViewController
@property (nonatomic, assign) NSInteger columnNumber;
@property (assign, nonatomic) BOOL isFirstAppear;
- (void)configTableView;
@end


@interface UIImage (MyBundle)
+ (UIImage *)imageNamedFromMyBundle:(NSString *)name;
@end


@interface NSString (TzExtension)
- (BOOL)tz_containsString:(NSString *)string;
- (CGSize)tz_calculateSizeWithAttributes:(NSDictionary *)attributes maxSize:(CGSize)maxSize;
@end


@interface TZCommonTools : NSObject
+ (BOOL)tz_isIPhoneX;
+ (CGFloat)tz_statusBarHeight;
// 获得Info.plist数据字典
+ (NSDictionary *)tz_getInfoDictionary;
@end


@interface TZImagePickerConfig : NSObject
+ (instancetype)sharedInstance;
@property (copy, nonatomic) NSString *preferredLanguage;
@property(nonatomic, assign) BOOL allowPickingImage;
@property (nonatomic, assign) BOOL allowPickingVideo;
@property (strong, nonatomic) NSBundle *languageBundle;
/// 默认是200，如果一个GIF过大，里面图片个数可能超过1000，会导致内存飙升而崩溃
@property (assign, nonatomic) NSInteger gifPreviewMaxImagesCount;
@end
