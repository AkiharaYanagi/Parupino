using System;
using System.ComponentModel;
using System.Windows.Forms;


namespace ScriptEditor
{
	//シークエンスの一覧をツリー状に表示し、選択を１つ返す
	//テキストのみ
	public class SequenceTree : UserControl
	{
		private TreeView treeView1;

		//シークエンスの選択デリゲート
		public System.Action < string > SelectSequence { get; set; } = null;

		//親Ctrl
		public Ctrl_Compend CtrlCompend { get; set; } = null;

		
		public SequenceTree ()
		{
			InitializeComponent ();
		}

		private void InitializeComponent ()
		{
			this.treeView1 = new System.Windows.Forms.TreeView();
			this.SuspendLayout();
			// 
			// treeView1
			// 
			this.treeView1.Dock = System.Windows.Forms.DockStyle.Fill;
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


		public void SetCharaData ( BindingDictionary < Sequence > bd_sq )
		{
			if ( null == bd_sq ) { return; }
			if ( 0 >= bd_sq.Count() ) { return; }

			BindingList < Sequence > bl = bd_sq.GetBindingList();

			treeView1.Nodes.Clear ();

			//アクションのときアクションカテゴリで分類
			if ( bl[0] is Action ) 
			{
				//アクションカテゴリで初期化
				string[] names = Enum.GetNames ( typeof ( ActionCategory ) );
				//木の根
				TreeNode[] root = new TreeNode [ names.Length ];

				int i = 0;
				foreach ( string name in names )
				{
					root [ i ] = new TreeNode ( name );
					++ i;
				}

				//各アクションを分類
				foreach ( Action a in bl )
				{
					string ctg_name = Enum.GetName ( typeof ( ActionCategory ), a.Category );
					int nodeIndex = 0;

					//カテゴリからサーチ
					foreach ( TreeNode n in root )
					{
						if ( ctg_name == n.Text )
						{
//							nodeIndex = n.Index;
							break;
						}
						++ nodeIndex;
					}

					//追加
					root [ nodeIndex ].Nodes.Add ( a.Name );
				}
				treeView1.Nodes.AddRange ( root );

				//先頭を選択
				treeView1.SelectedNode = root[0].Nodes[0];
				//EditCompend.SelectSequence ( root[0].Nodes[0].Text );
				SelectSequence ( root[0].Nodes[0].Text );
			}
			//アクションではない(エフェクト)のとき
			else
			{
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
				SelectSequence?.Invoke ( root [ 0 ].Text );
			}
		}

		//更新
		public void UpdateCategory ( Sequence sq )
		{
			//@todo ツリー選択時の再構築で順番が変わってしまう

			//アクションのときカテゴリの更新
			if ( sq is Action a )
			{
				//対象のアクションは１つだがすべてを走査しておく

				string ctg_name = Enum.GetName ( typeof ( ActionCategory ), a.Category );

				//すべてのノードから対象を削除
				foreach ( TreeNode nodes in treeView1.Nodes )
				{
					foreach ( TreeNode n0 in nodes.Nodes )
					{
						if ( a.Name == n0.Text )
						{
							n0.Remove ();
							break;
						}
					}
				}

				//カテゴリの正しい箇所へ追加
				foreach ( TreeNode nodes in treeView1.Nodes )
				{
					if ( ctg_name == nodes.Text )
					{
						nodes.Nodes.Add ( a.Name );
					}
				}

			}
		}

		//ツリー選択後
		private void treeView1_AfterSelect ( object sender, TreeViewEventArgs e )
		{
		}

		//ツリー選択前
		private void treeView1_BeforeSelect ( object sender, TreeViewCancelEventArgs e )
		{
			if ( treeView1.SelectedNode is null ) { return; }

			//選択名
			string name = treeView1.SelectedNode.Text;

			//アクション名以外(カテゴリ名など)の選択のとき何もしない
			string[] names = Enum.GetNames( typeof ( ActionCategory ) );
			foreach ( string s in names )
			{
				if ( s == name ) { return; }
			}

			//名前で選択
			SelectSequence?.Invoke ( name );

			//関連付け
			CtrlCompend.Assosiate ();

			//表示の更新
			DispChara.Inst.Disp ();
		}
	}
}
