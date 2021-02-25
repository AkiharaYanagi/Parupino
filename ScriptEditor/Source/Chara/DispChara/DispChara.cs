namespace ScriptEditor
{
	//==================================================================================
	//	キャラの表示
	//		アクションの集合ビヘイビア
	//		エフェクトの集合ガーニッシュを保持する
	//		シングルトンとしてグローバルからアクセス可能
	//==================================================================================
	public sealed class DispChara
	{
		//シングルトン実体
		public static DispChara Inst { get; } = new DispChara ();

		//コンペンドの表示 
		public DispBehavior DispBehavior { get; set; } = null;	//アクションの集合
		public DispGarnish DispGarnish { get; set; } = null;	//エフェクトの集合

		//---------------------------------------------------------------------
		//プライベートコンストラクタ
		private DispChara ()
		{
			DispBehavior = new DispBehavior ();
			DispGarnish = new DispGarnish ();
		}

		//読込時、コントールにキャラのデータを設定する
		public void SetCharaData ( Chara ch )
		{
			DispBehavior.SetCharaData ( ch );
			DispGarnish.SetCharaData ( ch );
		}

		//更新
		public void UpdateData ()
		{
			DispBehavior.UpdateData ();
			DispGarnish.UpdateData ();
		}

		//すべて描画
		public void Disp ()
		{
			DispBehavior.Disp ();
			DispGarnish.Disp ();
		}
	
	}


}
