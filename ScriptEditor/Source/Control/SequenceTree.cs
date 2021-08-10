using System;
using System.ComponentModel;
using System.Windows.Forms;
using System.Linq;


namespace ScriptEditor
{
	//------------------------------------------------------------------
	//	シークエンスの一覧をツリー状に表示し、テキストとして選択を１つ返す
	//------------------------------------------------------------------
	public class SequenceTree : UserControl
	{
		//ツリー表示
		private TreeView treeView1;

		//対象シークエンス
		public BindingDictionary < Sequence > BD_sq { get; set; } = null;


		//シークエンスの選択デリゲート
		//public System.Action < string > SelectSequence { get; set; } = null;
		public EditCompend EditCompend { get; set; } = null;

		//親Ctrl
		public Ctrl_Compend CtrlCompend { get; set; } = null;

		//コンストラクタ
		public SequenceTree ()
		{
			InitializeComponent ();
		}

		//コンポーネント初期化
		private void InitializeComponent ()
		{
			this.treeView1 = new System.Windows.Forms.TreeView();
			this.SuspendLayout();
			// 
			// treeView1
			// 
			this.treeView1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.treeView1.HideSelection = false;
			this.treeView1.Location = new System.Drawing.Point(0, 0);
			this.treeView1.Name = "treeView1";
			this.treeView1.Size = new System.Drawing.Size(129, 266);
			this.treeView1.TabIndex = 0;
			this.treeView1.BeforeSelect += new System.Windows.Forms.TreeViewCancelEventHandler(this.treeView1_BeforeSelect);
			this.treeView1.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.treeView1_AfterSelect);
			// 
			// SequenceTree
			// 
			this.AutoScroll = true;
			this.Controls.Add(this.treeView1);
			this.Name = "SequenceTree";
			this.Size = new System.Drawing.Size(129, 266);
			this.ResumeLayout(false);

		}

		//環境設定
		public void SetCtrl ( EditCompend ec )
		{
			EditCompend = ec;
		}

		//データ設定
		public void SetCharaData ( BindingDictionary < Sequence > bd_sq )
		{
			if ( null == bd_sq ) { return; }
			BD_sq = bd_sq;
			BindingList < Sequence > bl = bd_sq.GetBindingList();

			if ( 0 >= bd_sq.Count() ) { return; }


			//アクションのときのみアクションカテゴリで分類
			if ( bl[0] is Action ) 
			{
				//ツリー構築
				ClassficatinByCategory ( bl );

				//----------------------------------------------
				//先頭を選択
				treeView1.SelectedNode = treeView1.Nodes[0].Nodes[0];
				//SelectSequence?.Invoke ( treeView1.Nodes[0].Nodes[0].Text );
				string seq_name = treeView1.SelectedNode.Text;
				EditCompend.SelectSequence ( seq_name );
			}
			//アクションではない(エフェクト)のとき
			else
			{
				treeView1.Nodes.Clear ();

				//名前で直接分類する
				TreeNode [] root = new TreeNode [ bl.Count ];
			
				int index = 0;
				foreach ( Sequence s in bl )
				{
					root [ index ] = new TreeNode ( s.Name );
					++ index;
				}

				treeView1.Nodes.AddRange ( root );


				//先頭を選択
				treeView1.SelectedNode = root[0];

				//設定デリゲートが存在したら実行
//				SelectSequence?.Invoke ( root [ 0 ].Text );
				EditCompend.SelectSequence ( root [ 0 ].Text );
			}
		}

		//更新
		public void UpdateCategory ( BindingList < Sequence > bl )
		{
			//@todo ツリー選択時の再構築で順番が変わってしまう
			//->コンペンドの選択イベントでUpdateが呼ばれる

			//全開放->対象コンペンドからツリーを再構築して順番を保持する

			if ( bl is null ) { return; }
			if ( bl.Count <= 0 ) { return; }

			//アクションのときカテゴリの更新
			if ( bl[0] is Action a )
			{
				ClassficatinByCategory ( bl );
			}
		}

		//再構築
		public void Remake ()
		{
			ReExpand ();
			UpdateCategory ( BD_sq.GetBindingList () );
			tmpNd?.Expand ();
		}

		//ツリー選択後
		private void treeView1_AfterSelect ( object sender, TreeViewEventArgs e )
		{
			if ( treeView1.SelectedNode is null ) { return; }

			//アクションのときのみ
			BindingList < Sequence > bl = BD_sq.GetBindingList ();
			TreeNode slctNd = treeView1.SelectedNode;

			if ( bl[0] is Action a )
			{
				//カテゴリのときは何もしない
				foreach ( TreeNode tn in treeView1.Nodes )
				{
					if ( tn == slctNd ) { return; }
				}
				slctNd.Parent.Expand ();
			}

			//選択名
			string name = treeView1.SelectedNode.Text;

			//名前で選択
			//SelectSequence?.Invoke ( name );
			EditCompend.SelectSequence ( name );

			//関連付け
			CtrlCompend.Assosiate ();

			//表示の更新
			DispChara.Inst.Disp ();

			//ツリーの展開
//			treeView1.ExpandAll ();
//			TreeNode[] tna = treeView1.Nodes.Find ( name, true );
//			tna[0].Expand ();
//			slctNd.Expand ();
			tmpNd?.Expand ();

		}

		//ツリー選択前
		private void treeView1_BeforeSelect ( object sender, TreeViewCancelEventArgs e )
		{
			ReExpand ();	
		}

		//選択済みノードを一時保存して再展開
		private TreeNode tmpNd = null;	//選択を一時保存
		public void ReExpand ()
		{
			TreeNode tn = treeView1.SelectedNode;
			if ( tn is null ) { return; }

			BindingList < Sequence > bl = BD_sq.GetBindingList ();
			//アクションの場合
			if ( bl[0] is Action a )
			{
				//カテゴリを保存
				tmpNd = tn.Parent;;
			}
			else
			{
				tmpNd = treeView1.SelectedNode;
			}
		}


		//カテゴリでツリーを再構築
		private void ClassficatinByCategory ( BindingList < Sequence > bl )
		{
			//クリア
			treeView1.Nodes.Clear ();

			//----------------------------------------------
			//定数でカテゴリを初期化
			string[] names = Enum.GetNames ( typeof ( ActionCategory ) );

			//木の根
			TreeNode[] root = new TreeNode [ names.Length ];

			//追加
			for ( int i = 0; i < names.Length; ++ i )
			{
				root [ i ] = new TreeNode ( names [ i ] );
			}

			//----------------------------------------------
			//各アクションを分類
			foreach ( Action a in bl )
			{
				//カテゴリ名を取得
				string ctg_name = Enum.GetName ( typeof ( ActionCategory ), a.Category );

				//カテゴリからサーチ
				TreeNode tn = Array.Find ( root, n => n.Text == ctg_name );

				//追加
				tn.Nodes.Add ( a.Name );				
			}

			//----------------------------------------------
			//全追加
			treeView1.Nodes.AddRange ( root );

		}
	}
}
